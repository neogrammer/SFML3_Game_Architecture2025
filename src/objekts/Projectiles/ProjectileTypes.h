#ifndef PROJECTILETYPES_H__
#define PROJECTILETYPES_H__

namespace proj
{
	enum class DirType : int
	{
		Horizontal = 0,
		Vertical = 1,
		Path = 2,
		Orbiting = 3,
		Spiral = 4
	};

	enum class DmgType : int
	{
		AOE = 0,
		DOT = 1,
		Burst = 2
	};
}

#endif