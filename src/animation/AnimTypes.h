#ifndef ANIMTYPES_H__
#define ANIMTYPES_H__

enum class AnimName
{
	Idle,
	Fly,
	Invariant
};

enum class AnimState
{
	Playing,
	Transient,
	LoopWaiting,
	Stopped,
	Invariant
};

enum class AnimDir
{
	Left,
	Right,
	Uni,
	Invariant
};

#endif