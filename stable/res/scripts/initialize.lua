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
				delay = 1000,
				{ 1, 1 },
				{ 2, 1 },
				{ 3, 1 },
				{ 4, 1 },

				{ 1, 2 },
				{ 2, 2 },
				{ 3, 2 },
				{ 4, 2 }
			},
		}
	},
	event_component = {
		key_down = function(self, key)
			print('Key was pressed')
		end,
		
		key_up = function(self, key)
			print('Key was released')
		end,
		
		left_click = function(self, key)
			
		end,
		
		right_click = function(self, key)
			
		end
	}
}

























--[[

entity = require('entity')
map = {
	{0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,1,0},
	{0,0,0,1,0,0,0,0}
}

player = entity.new({
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
				delay = 1000,
				{ 1, 1 },
				{ 2, 1 },
				{ 3, 1 },
				{ 4, 1 },
				{ 1, 2 },
				{ 2, 2 },
				{ 3, 2 },
				{ 4, 2 }
			},
		}
	},
	event_component = {
		key_down = function(self, key)
			print('Key was pressed')
		end,
		
		key_up = function(self, key)
			print('Key was released')
		end,
		
		left_click = function(self, key)
			
		end,
		
		right_click = function(self, key)
			
		end
	}
})

]]