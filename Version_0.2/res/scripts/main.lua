print("Lua initialized")
engine:create{
	name = "Background",
	dimension = {
		width = 800,
		height = 600
	},
	position = {
		x = 400,
		y = 300
	},
	image = {
		src = "../../res/images/GT_1.0_TEST.png"
	}
}

engine:create{
	name = "Player",
	dimension = {
		width = 90,
		height = 180
	},
	position = {
		x = 400,
		y = 300
	},
	image = {
		src = "../../res/images/TB1.0.png"
	}
}
