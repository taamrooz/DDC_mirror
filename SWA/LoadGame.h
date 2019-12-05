#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include "Renderer.h"
#include <vector>
#include <memory>
#include <string>
#include <Texture.h>

class LoadGame :
	virtual public Engine::BaseScene
{
private:
	std::string text_;
	std::string load_game_file_name_;
	std::vector<std::string> file_names_;
	std::vector<std::unique_ptr<Texture>> file_name_textures_;
	std::unique_ptr<Texture> text_texture_ = nullptr;
public:
	~LoadGame();
	LoadGame(Engine::SceneManager* manager);
	void render() override;
	void cleanup() override;
	void get_files(const char* path, const std::string extension);
	void input_load_game(SDL_Keycode keycode, std::string& text);
	void input();
};