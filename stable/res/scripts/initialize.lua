print('Lua Initialized')
window = {
	title = 'Test Window',
	width = 800,
	height = 600
}

player = { 
	graphics_component = {
		file = '../../res/images/TP_1.0_SpriteSheet.png',
		x = window.width / 2.0,
		y = window.height / 2.0,
		scale = 6.0,
		width = 11,
		height = 18,
		rotation = 0.0,
		
		animations = {
			walk_right = {
				delay = 250,
				{ 2, 1 },
				{ 3, 1 },
			},
			stop_right = {
				{ 1, 1 }
			},
			walk_left = {
				delay = 250,
				{ 2, 2 },
				{ 3, 2 },
			},
			stop_left = {
				{ 1, 2 }
			}
		}
	},
	
	event_component = {
		key_down = function(self, key)
			if key == 'a' then
				self.x = self.x - 5
				self:set_animation('walk_left')
			elseif key == 'd' then
				self.x = self.x + 5
				self:set_animation('walk_right')
			elseif key == ' ' then
				self.rotation = self.rotation + 30
			end
		end,
		
		key_up = function(self, key)
			if key == 'a' then
				self:set_animation('stop_left')
			elseif key == 'd' then
				self:set_animation('stop_right')
			end
		end,
		
		left_click = function(self, x, y)
			self.x = x
			self.y = y
		end,
		
		right_click = function(self, x, y)
			self.x = math.random(0, window.width)
			self.y = math.random(0, window.height)
		end
	}
}
