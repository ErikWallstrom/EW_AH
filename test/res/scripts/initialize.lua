print('Lua Initialized')
window = {
	title = 'Test Window',
	width = 800,
	height = 600
}

player = { 
	image_component = {
		file = '../../res/images/TP_1.0_SpriteSheet.png',
		x = 350.0,
		y = 250.0,
		scale = 6.0,
		width = 9,
		height = 18,
		rotation = 0.0,
		
		animations = {
			walk_right = {
				delay = 1000,
				{ 1, 1 },
				{ 2, 1 }
			},
			
			walk_right = {
				delay = 1000,
				{ 1, 2 },
				{ 2, 2 }
			},
		}
	},
	
	text_component = {
		
	}
}

