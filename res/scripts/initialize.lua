print('Lua Initialized')

--Set window properties
window = {
	title = 'Test Window',
	width = 800,
	height = 600
}

--Create a player entity with a graphics component
player = { graphics_component = {} }

--File path of sprite sheet
player.graphics_component.file = '../../res/images/TP_1.0_SpriteSheet.png'

--The time that each frame shows in milliseconds
player.graphics_component.delay = 500

--Specify sprites in sprite sheet
player.graphics_component.frames = {
	frame1 = {
		--X and Y position in sprite sheet
		x = 0,
		y = 0
	},
	frame2 = {
		x = 11,
		y = 0
	},
	frame3 = {
		--X and Y position in sprite sheet
		x = 22,
		y = 0
	},
	frame4 = {
		x = 33,
		y = 0
	},
	frame5 = {
		--X and Y position in sprite sheet
		x = 0,
		y = 18
	},
	frame6 = {
		x = 11,
		y = 18
	},
	frame7 = {
		--X and Y position in sprite sheet
		x = 22,
		y = 18
	},
	frame8 = {
		x = 33,
		y = 18
	},
	--frame3...
}

--The scale the sprite shown in window is
player.graphics_component.scale = 6

--Width and height of each sprite in sprite sheet
player.graphics_component.width = 11
player.graphics_component.height = 18

--X and Y position in window (in pixels)
player.graphics_component.x = window.width / 2 - (player.graphics_component.width / 2) * player.graphics_component.scale
player.graphics_component.y = window.height / 2 - (player.graphics_component.height / 2) * player.graphics_component.scale
