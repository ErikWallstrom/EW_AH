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
player.graphics_component.delay = 1000

--Specify sprites in sprite sheet
player.graphics_component.frames = {
	frame1 = {
		--X and Y position in sprite sheet
		x = 9,
		y = 0
	},
	frame2 = {
		x = 18,
		y = 0
	},
	--frame3...
}

--X and Y position in window (in pixels)
player.graphics_component.x = 350.0
player.graphics_component.y = 250.0

--The scale the sprite shown in window is
player.graphics_component.scale = 6

--Width and height of each sprite in sprite sheet
player.graphics_component.width = 9
player.graphics_component.height = 18
