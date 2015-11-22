print('Lua Initialized')

window = {
	title = 'Test Window',
	width = 800,
	height = 600
}

player = {
	graphics_component = {
		file = '../../res/images/TB1.0.png', 	--Sprite sheet file path
		delay = 1000,							--1000 milliseconds delay between frames
		frames = {
			frame1 = {
				x = 0,							--X position in sprite sheet
				y = 0							--Y position in sprite sheet
			},
			frame2 = {
				x = 7,
				y = 0
			}
		},
		
		scale = 6,
		width = 7,
		height = 16,
		
		x = 350.0,								--X position of player
		y =	250.0								--Y position of player
	}
}