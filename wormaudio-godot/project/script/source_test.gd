extends Node3D

var instance

func _ready():
	#instantiate_sound()
	pass

func _physics_process(_delta: float) -> void:
	#WARuntime.set_param_val("tension", -60)
	#WARuntime.set_param_val("end", 1)
	pass


func instantiate_sound() -> void:
	var sys: WASystemNode = get_node("%system")
	var def = sys.get_sound_def("music")
	instance = WARuntime.instantiate(def)
	instance.set_state(WATransport.STARTING)
	instance.set_position(global_position)
	pass
