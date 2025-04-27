#pragma once

#include <game_objects/Player.h>

#include <algorithm> // for std::max, std::min, and std::swap
#include <game_objects/SimplePlatform.h>

class Physics
{
    static const int Gravity;
public:
    //======================================================
    //  Basic AABB collision check between two GameObjects
    //======================================================
    static void applyGravity(GameObject& obj_, float dt_)
    {
        obj_.setVelocity({ obj_.getVelocity().x, obj_.getVelocity().y + (Gravity * dt_)});
    };

    static bool checkCollision(GameObject* objA, GameObject* objB, float& length)
    {
        // We assume objA is a DynamicObject and objB is a StaticObject
        // (or we can handle other combos in the future if we want)
        auto* dyno = objA;
        auto* stat = objB;
        if (!dyno || !stat) return false;

        float leftA = dyno->getPosition().x;
        float rightA = dyno->getPosition().x + dyno->getWorldSize().x;
        float topA = dyno->getPosition().y;
        float bottomA = dyno->getPosition().y + dyno->getWorldSize().y;

        float leftB = stat->getPosition().x;
        float rightB = stat->getPosition().x + stat->getWorldSize().x;
        float topB = stat->getPosition().y;
        float bottomB = stat->getPosition().y + stat->getWorldSize().y;
        if (leftA < rightB && rightA > leftB && topA < bottomB && bottomA > topB)
        {
            // in collision, figure out length from center to center
            sf::Vector2f centerToCenter = { (leftB + (stat->getWorldSize().x / 2.f)) - (leftA + (dyno->getWorldSize().x / 2.f)),
                                                                 (topB + (stat->getWorldSize().y / 2.f)) - (topA + (dyno->getWorldSize().y / 2.f)) };

            length = sqrt(centerToCenter.x * centerToCenter.x + centerToCenter.y * centerToCenter.y);
        }
        else
        {
            length = -1.f;
        }
        return (leftA < rightB&& rightA > leftB && topA < bottomB&& bottomA > topB);
    }

    //======================================================
    //  Simple bounding box checks using just positions/sizes
    //======================================================
    static bool ptVrect(const sf::Vector2f pos, const sf::Vector2f rectPos, const sf::Vector2f rectSize)
    {
        return (pos.x < rectPos.x + rectSize.x &&
            pos.x > rectPos.x &&
            pos.y < rectPos.y + rectSize.y &&
            pos.y > rectPos.y);
    }

    static bool rectVrect(const sf::Vector2f posA, const sf::Vector2f sizeA,
        const sf::Vector2f posB, const sf::Vector2f sizeB)
    {
        return (posA.x < posB.x + sizeB.x &&
            (posA.x + sizeA.x) > posB.x &&
            posA.y < posB.y + sizeB.y &&
            (posA.y + sizeA.y) > posB.y);
    }

    //======================================================
    //  rayVrect - Swept collision test for a ray vs. a rect
    //======================================================
    static bool rayVrect(sf::Vector2f halfsz,
        sf::Vector2f ray_origin,
        sf::Vector2f ray_dir,
        sf::Vector2f targetPos,
        sf::Vector2f targetSize,
        sf::Vector2f& cp,
        sf::Vector2f& cn,
        float& t_hit_near,
        float dt)
    {
        // Calculate near/far intersection times for each axis
        sf::Vector2f t_near{
            (targetPos.x - ray_origin.x) / ray_dir.x,
            (targetPos.y - ray_origin.y) / ray_dir.y
        };

        sf::Vector2f t_far{
            (targetPos.x + targetSize.x - ray_origin.x) / ray_dir.x,
            (targetPos.y + targetSize.y - ray_origin.y) / ray_dir.y
        };

        // Ensure t_near.x <= t_far.x etc.
        if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
        if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

        // If intervals don't overlap, no collision
        if (t_near.x > t_far.y || t_near.y > t_far.x)
            return false;

        // Find the largest near collision time
        t_hit_near = std::max(t_near.x, t_near.y);
        float t_hit_far = std::min(t_far.x, t_far.y);

        // If the far intersection is behind origin, no collision
        if (t_hit_far < 0)
            return false;

        // Contact point = ray_origin + t_hit_near * ray_dir
        cp.x = ray_origin.x + t_hit_near * ray_dir.x;
        cp.y = ray_origin.y + t_hit_near * ray_dir.y;

        // Contact normal
        if (t_near.x > t_near.y)
        {
            cn = (ray_dir.x < 0) ? sf::Vector2f{ 1.f, 0.f } : sf::Vector2f{ -1.f, 0.f };
        }
        else if (t_near.x < t_near.y)
        {
            cn = (ray_dir.y < 0) ? sf::Vector2f{ 0.f, 1.f } : sf::Vector2f{ 0.f, -1.f };
        }

        // Return true if collision occurs within this timestep
        return (t_hit_near >= 0.f && t_hit_near < 1.f);
    }

    //======================================================
    //  dynamicVrect - Swept collision test for a moving rect
    //                 vs. a static rect
    //======================================================
    static bool dynamicVrect(sf::Vector2f& posA,
        sf::Vector2f sizeA,
        sf::Vector2f& vel,
        sf::Vector2f targetPos,
        sf::Vector2f targetSize,
        sf::Vector2f& cp,
        sf::Vector2f& cn,
        float& ct,
        float dt)
    {
        // If not moving, no collision
        if (vel.x == 0 && vel.y == 0)
            return false;

        // Expand target by size of moving rect so we treat it like
        // we’re casting a single point (the center) vs. an expanded rect
        sf::Vector2f expandedPos{
            targetPos.x - (sizeA.x / 2.f),
            targetPos.y - (sizeA.y / 2.f)
        };
        sf::Vector2f expandedSize{
            targetSize.x + sizeA.x,
            targetSize.y + sizeA.y
        };

        // Now cast a ray from the center of the dynamic rect
        sf::Vector2f rayOrigin{
            posA.x + sizeA.x / 2.f,
            posA.y + sizeA.y / 2.f
        };
        sf::Vector2f rayDir{ vel.x * dt, vel.y * dt };

        // We'll assume halfsz is half the dynamic rect,
        // or set it to 0 if you prefer a "point" test
        sf::Vector2f halfsz{ sizeA.x / 2.f, sizeA.y / 2.f };

        // If we collide with expanded rect, we get cp, cn, ct
        if (rayVrect(halfsz, rayOrigin, rayDir,
            expandedPos, expandedSize,
            cp, cn, ct, dt))
        {
            // ct is the "time of impact". If 0 <= ct < 1 => collision within frame
            if (ct < 1.f && ct >= 0.f)
                return true;
        }
        return false;
    }

    //======================================================
    //  Example of a simple collision resolution 
    //  (dynamic vs static)
    //======================================================
    static void resolveCollision(GameObject* dynamicObj, GameObject* staticObj)
    {
        float len;
        // If no overlap, nothing to do
        if (!checkCollision(dynamicObj, staticObj, len))
            return;

        float leftD = dynamicObj->getPosition().x;
        float rightD = dynamicObj->getPosition().x + dynamicObj->getWorldSize().x;
        float topD = dynamicObj->getPosition().y;
        float bottomD = dynamicObj->getPosition().y + dynamicObj->getWorldSize().y;

        float leftS = staticObj->getPosition().x;
        float rightS = staticObj->getPosition().x + staticObj->getWorldSize().x;
        float topS = staticObj->getPosition().y;
        float bottomS = staticObj->getPosition().y + staticObj->getWorldSize().y;

        float overlapLeft = rightD - leftS;
        float overlapRight = rightS - leftD;
        float overlapTop = bottomD - topS;
        float overlapBottom = bottomS - topD;

        float minOverlap = overlapLeft;
        std::string axis = "Left";

        // Check each axis for the smallest overlap
        if (overlapRight < minOverlap)
        {
            minOverlap = overlapRight;
            axis = "Right";
        }
        if (overlapTop < minOverlap)
        {
            minOverlap = overlapTop;
            axis = "Top";
        }
        if (overlapBottom < minOverlap)
        {
            minOverlap = overlapBottom;
            axis = "Bottom";
        }

        // Adjust position along the axis of smallest overlap
        float newX = dynamicObj->getPosition().x;
        float newY = dynamicObj->getPosition().y;

        if (axis == "Left")
        {
            newX -= minOverlap;
            dynamicObj->setVelocity({0.f, dynamicObj->getVelocity().y});

            auto* b = dynamic_cast<Projectile*>(dynamicObj);
            if (b)
            {
                b->collide(staticObj);
            }

        }
        else if (axis == "Right")
        {
            newX += minOverlap;
            dynamicObj->setVelocity({  0.f,dynamicObj->getVelocity().y });

            auto* b = dynamic_cast<Projectile*>(dynamicObj);
            if (b)
            {
                b->collide(staticObj);
            }
        }
        else if (axis == "Top")
        {
            auto* p = dynamic_cast<Player*>(dynamicObj);

            if (p != nullptr) // dynamicObj is the player, lets set the canJump flag to true, they just landed
            {
                

                
                p->canJump = true;
                p->fsm.dispatch(EventLanded{});
                    




                 newY -= minOverlap;

                  dynamicObj->setVelocity({ dynamicObj->getVelocity().x, 0.f });
                
                
            }
            else
            {
                newY -= minOverlap;

                dynamicObj->setVelocity({ dynamicObj->getVelocity().x, 0.f });

            }


            // we landed, if it was onto a platform, attach that object to the platform
            auto* plat = dynamic_cast<SimplePlatform*>(staticObj);
            if (plat != nullptr)
            {
                plat->attach(dynamicObj);
            }



        }
        else if (axis == "Bottom")
        {
            auto* p = dynamic_cast<Player*>(dynamicObj);
            if (p != nullptr) // dynamicObj is the player, lets set the canJump flag to true, they just landed
            {
                p->fsm.dispatch(EventFell{});
            }
            newY += minOverlap;
            dynamicObj->setVelocity({ dynamicObj->getVelocity().x, 0.f });
        }

       
        dynamicObj->setPosition({ newX, newY });
        
    }
};
