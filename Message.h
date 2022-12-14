#pragma once

enum class Message {
	HIT, ROBOT_HIT, SCORE, ADDBONUS,
	GAME_OVER, LEVEL_WIN,
	SOUTH, NORTH, EAST, WEST, SOUTHEAST, SOUTHWEST, NORTHEAST, NORTHWEST,
	UP, LEFT, DOWN, RIGHT, NEW_ROOM,
	WALL, PLAYER, SPAWN_SENTRY, DESPAWN_SENTRY,
	TRACK_X, TRACK_Y,
	YELLOWBOT, REDBOT, CYANBOT, BLACKBOT,
	NO_MSG
};