#include "Advertisement.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"
#include <Audio.h>

Advertisement::~Advertisement() = default;

Advertisement::Advertisement(Engine::SceneManager* manager) : BaseScene(manager) { }

void Advertisement::render() {
	const auto timer = Engine::pre_update();
	input();

	Engine::update_animation(advertisement_.get(), 250, 50);
	Engine::render_texture(exit_.get(), 250, 200, nullptr);
}

void Advertisement::input() {
	constexpr static int k_keydown = 0;
	constexpr static int k_stop = 2;

	auto inputs = Engine::GetInputs();

	//Quit if user wants to exit
	if (!std::get<k_stop>(inputs)) {
		is_running_ = false;
		return;
	}

	//Handle all key down events
	for (const auto& keycode : std::get<k_keydown>(inputs))
	{
		if (keycode == SDLK_RETURN)
		{
			break;
		}
	}
}

void Advertisement::cleanup() {}

bool Advertisement::init() {
	advertisement_ = std::make_unique<Animation>(*Engine::load_animation("mediamarkt.png", 1, true));
	exit_ = std::make_unique<Texture>(*Engine::load_tileset("Sprites/delete.png"));
	return true;
}