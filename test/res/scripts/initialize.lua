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
			},
		}
	},
	
	event_component = {
		key_down = function(self, key)
			if key == 'a' then
				self:set_animation('walk_left')
				self.x = self.x - math.cos(math.rad(self.rotation)) * 5
				self.y = self.y - math.sin(math.rad(self.rotation)) * 5
			elseif key == 'd' then
				self:set_animation('walk_right')
				self.x = self.x + math.cos(math.rad(self.rotation)) * 5
				self.y = self.y + math.sin(math.rad(self.rotation)) * 5
			elseif key == 'q' then
				self.rotation = self.rotation - 3
			elseif key == 'e' then	
				self.rotation = self.rotation + 3
			elseif key == 'f' then
				self.rotation = self.rotation - 180
			elseif key == 'o' then
				self.scale = self.scale - 0.1
			elseif key == 'p' then
				self.scale = self.scale + 0.1
			elseif key == 'r' then
				self.x = window.width / 2
				self.y = window.height / 2
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
			--self.rotation = math.deg(math.atan2(self.y - y, self.x - x)) + 180
		end,
		
		right_click = function(self, x, y)
			--self.rotation = math.deg(math.atan2(self.y - y, self.x - x))
		end
	}
}
