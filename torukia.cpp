#include "torukia.hpp"

#include <sstream>

namespace Torukia {

SDL_Window *TorukiaEngine::get_sdl_window() const {
	return _sdl_window;
}

SDL_Renderer *TorukiaEngine::get_sdl_renderer() const {
	return _sdl_renderer;
}

bool TorukiaEngine::init_sdl() {
	bool sdl_video = false;
	Uint32 sdl_window_flags = 0;

	Uint32 sdl_flags = 0;
	if( !(_init_flags & InitFlags::no_video) ){
		sdl_video = true;
		sdl_flags += SDL_INIT_VIDEO;
	}
	if( !(_init_flags & InitFlags::no_sound) ){
		sdl_flags += SDL_INIT_SOUND;
	}
	if( !(_init_flags & InitFlags::no_input) ){
		sdl_flags += SDL_INIT_EVENT;
	}
	if( _init_flags & InitFlags::set_opengl_context ){
		sdl_window_flags = SDL_WINDOW_OPENGL;
	}

	if( SDL_Init(sdl_flags) != 0){
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	if(sdl_video) 
		SDL_CreateWindowAndRenderer(m_window_width,
									m_window_height,
									sdl_window_flags,
									&_sdl_window,
									&_sdl_renderer);
	return 0;
}

bool TorukiaEngine::clean_sdl() {
	SDL_Quit();
}

int TorukiaEngine::run(const int flags) {
	std::cout << "Running instance." << std::endl;
	if(init_sdl()){
		std::cout << "Torukia run aborded." << std::endl;
		clean_sdl();
		return 1;
	}
	while(!SDL_QuitRequested()){
		if( !(_init_flags & InitFlags::no_logic) )
			user_logic();
		if( !(_init_flags & InitFlags::no_video) )
			user_view();
	}

	clean_sdl();
	return 0;
}

std::string TorukiaEngine::game_instance_name() const {
	return _game_instance_name;
}

int TorukiaEngine::init_flags() const {
	return _init_flags;
}

std::string TorukiaEngine::get_init_flags_info() const {
	std::stringstream out;

	if(_init_flags & TorukiaEngine::InitFlags::no_video)
		out << "No video set." << std::endl;
	if(_init_flags & TorukiaEngine::InitFlags::no_sound)
		out << "No sound set." << std::endl;
	if(_init_flags & TorukiaEngine::InitFlags::no_input)
		out << "No input set." << std::endl;
	if(_init_flags & TorukiaEngine::InitFlags::no_logic)
		out << "No logic set." << std::endl;
	if(_init_flags & TorukiaEngine::InitFlags::set_opengl_context)
		out << "OpenGL is set." << std::endl;

	return out.str();
}

int TorukiaEngine::context_flags() const {
	return _context_flags;
}

std::string TorukiaEngine::get_context_flags_info() const{
	std::stringstream out;

	if(_context_flags & TorukiaEngine::ContextFlags::error_n_1)
		out << "Error." << std::endl;
	if(_context_flags & TorukiaEngine::ContextFlags::error_user_code)
		out << "User code fail." << std::endl;

	return out.str();
}

std::string TorukiaEngine::get_all_info() const {
	std::stringstream out;

	out << _game_instance_name 
	    << "TorukiaEngine object instance at memory: "
	    << this
	    << std::endl;
	out << "   Init flags set -> " << std::endl;
	out << get_init_flags_info();
	out << "   Context flags set -> " << std::endl;
	out << get_context_flags_info();

	return out.str();
}
void TorukiaEngine::set_context_flags(const ContextFlags flag, const bool value) {
	unsigned int log2 = 0;
	int buffer_flag = flag;
	while (buffer_flag >>= 1) { ++log2; }

	this->_context_flags ^= (-(unsigned int)(value?1:0) ^ _context_flags) & (1UL << log2);
}

void TorukiaEngine::set_context_flags(const int32_t flags) {
	this->_context_flags = flags;
}

}