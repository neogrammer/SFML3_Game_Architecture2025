#ifndef PHYSICS_H__
#define PHYSICS_H__
#include <algorithm> // for std::max, std::min, and std::swap
#include <GameObjects/Player/PlayerObj.h>
#include <FSM/Events.h>

class Physics
{
public:
    static float Gravity;
    //======================================================
    //  Basic AABB collision check between two GameObjects
    //======================================================
    static bool checkCollision(PlayerObj* objA, GObj* objB, float& length)
    {
        // We assume objA is a DynamicObject and objB is a StaticObject
        // (or we can handle other combos in the future if we want)
        //auto* dyno = dynamic_cast<DynamicObject*>(objA);
        //auto* stat = dynamic_cast<StaticObject*>(objB);
        //if (!dyno || !stat) return false;

        float leftA = objA->getPos().x;
        float rightA = objA->getPos().x + objA->getSize().x;
        float topA = objA->getPos().y;
        float bottomA = objA->getPos().y + objA->getSize().y;
        float leftB, rightB, topB, bottomB;

        leftB = objB->getPos().x;
        rightB = objB->getPos().x + objB->getSize().x;
        topB = objB->getPos().y;
        bottomB = objB->getPos().y + objB->getSize().y;

        if (leftA < rightB && rightA > leftB && topA < bottomB && bottomA > topB)
        {
            // in collision, figure out length from center to center
            sf::Vector2f centerToCenter = { (leftB + (objB->getSize().x / 2.f)) - (leftA + (objA->getSize().x / 2.f)),
                                                                 (topB + (objB->getSize().y / 2.f)) - (topA + (objA->getSize().y / 2.f)) };

            length = sqrt(centerToCenter.x * centerToCenter.x + centerToCenter.y * centerToCenter.y);
        }
        else
        {
            length = -1.f;
        }
        return (leftA < rightB && rightA > leftB && topA < bottomB && bottomA > topB);
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
    static void resolveCollision(PlayerObj* dynamicObj, GObj* staticObj)
    {
        float len;
        if (!dynamicObj || !staticObj) { return; }
        // If no overlap, nothing to do
        if (!checkCollision(dynamicObj, staticObj, len))
            return;

        float leftD = dynamicObj->getPos().x;
        float rightD = dynamicObj->getPos().x + dynamicObj->getSize().x;
        float topD = dynamicObj->getPos().y;
        float bottomD = dynamicObj->getPos().y + dynamicObj->getSize().y;
        float leftS, rightS, topS, bottomS;
        leftS = staticObj->getPos().x;
        rightS = staticObj->getPos().x + staticObj->getSize().x;
        topS = staticObj->getPos().y;
        bottomS = staticObj->getPos().y + staticObj->getSize().y;

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
        float newX = dynamicObj->getPos().x;
        float newY = dynamicObj->getPos().y;

        if (axis == "Left")
        {
            newX -= minOverlap;
            //dynamicObj->SetVelocity({ dynamicObj->GetVelocity().x, 0.f });
            dynamicObj->setVelocity({ 0.f, dynamicObj->getVelocity().y });

        }
        else if (axis == "Right")
        {
            newX += minOverlap;
            dynamicObj->setVelocity({ 0.f,  dynamicObj->getVelocity().y });
            //            dynamicObj->SetVelocity({ dynamicObj->GetVelocity().x, 0.f });

        }
        else if (axis == "Top")
        {
            newY -= minOverlap;
            //         dynamicObj->SetVelocity({ dynamicObj->GetVelocity().x, 0.f });
            dynamicObj->setVelocity({ dynamicObj->getVelocity().x, 0.f });

            if (!dynamicObj->isOnGround())
            {
                if (dynamic_cast<PlayerObj*>(dynamicObj) != nullptr)
                {
                    auto* p = dynamic_cast<PlayerObj*>(dynamicObj);
                    p->handleEvent(EventLanding{ (fabsf(p->getVelocity().x) > 0.01f) });
                }
            }
            dynamicObj->setOnGround(true);




            /* setAnimation("Idle");

                 if (std::abs(dynamic_cast<Player*>(dynamicObj)->currVelocity().x) >= 0.01f)
                     dynamic_cast<Player*>(dynamicObj)->setAnimation("Walk");*/

                     //dynamic_cast<Player*>(dynamicObj)->setCanJump(true);


        }
        else if (axis == "Bottom")
        {
            newY += minOverlap;
            //      dynamicObj->SetVelocity({ dynamicObj->GetVelocity().x, 0.f });
            dynamicObj->setVelocity({ dynamicObj->getVelocity().x, 0.f });

        }

        dynamicObj->setPos({ newX, newY });
    }
};


#endif