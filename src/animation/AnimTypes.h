#ifndef ANIMTYPES_H__
#define ANIMTYPES_H__

enum class AnimName
{
	Idle,
	Fly,
	IdleToRun,
	Running,
	RunToIdle,
	ShootSetup,
	Shooting,
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

enum class AnimSheetType
{
	Normal,
	Padded,
	Blocks,
	Vertical
};

#endif