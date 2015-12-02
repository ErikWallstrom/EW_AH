print('Lua Initialized')
window = {
	title = 'Test Window',
	width = 800,
	height = 600
}

player = { 
	graphics_component = {
		file = '../../res/images/TP_1.0_SpriteSheet.png',
		x = 350.0,
		y = 250.0,
		scale = 6.0,
		width = 11,
		height = 18,
		rotation = 0.0,
		
		animations = {
			walk_right = {
				{ 1, 1 },
				{ 2, 1 },
				{ 3, 1 },
				delay = 1000
			},
			
			walk_left = {
				delay = 1000,
				{ 1, 2 },
				{ 2, 2 }
			},
		}
	}
}
