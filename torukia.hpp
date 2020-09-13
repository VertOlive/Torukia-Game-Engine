/** 
 * @file		torukia.hpp
 * @author		Tarek Hanna EL SAIDI
 * @version		0.1 <still prototype>
 */

#ifndef TORUKIA_H
#define TORUKIA_H

#include <cstdint>

#include <iostream>
#include <string>

#ifdef _WIN32
 #include <SDL.h>
#else
 #include <SDL2/SDL.h>
#endif

namespace Torukia {

/** @class TorukiaEngine torukia.hpp "header/torukia.hpp"
 *  @brief Constructor of the TorukiaEngine game engine class
 *
 *  TorukiaEngine use SDL2 motor for graphics, sounds and input and have
 *  a file to user logic.
 */
class TorukiaEngine {
private:
	SDL_Window *_sdl_window;
	SDL_Renderer *_sdl_renderer;

	std::string _game_instance_name;

	unsigned int m_window_width;
	unsigned int m_window_height;
	unsigned int m_window_pos_x;
	unsigned int m_window_pos_y;

protected:
	const int32_t _init_flags;   /**< Flags set at the creation of the instance, not given to the user code */
	int32_t _context_flags;      /**< Flags */
	int32_t _user_flags;         /**< Flags set at the run methode call, given to the user code logic */

	SDL_Window *get_sdl_window() const;
	SDL_Renderer *get_sdl_renderer() const;
	/** @fn void set_context_flags(ContextFlags flag)
	 *  @bref Set the context flags of the instance.
	 */
	void set_context_flags(const ContextFlags flag, const bool value);
	/** @fn void set_context_flags(const int flags)
	 *  @bref Set the context flags of the instance.
	 */
	void set_context_flags(const int32_t flags);
	virtual bool user_logic() {};
	virtual void user_view() {};
public:
	/** @enum TorukiaEngine::InitFlags
	 *  Flags for instansiation of the objet TorukiaEngine.
	 */
	enum InitFlags {
		no_video = 1,
		no_sound = 2,
		no_input = 4,
		no_logic = 8,
		set_opengl_context = 16
	};
	/** @enum TorukiaEngine::ContextFlags
	 *  Intern flags of the object TorukiaEngine.
	 */
	enum ContextFlags {
		error_n_1 = 1,
		error_user_code = 2
	};
	/** @brief Constructor of the TorukiaEngine game engine class.
	 *
	 *  Create an object representing the instance of the game engine
	 *  TorukiaEngine.
	 *
	 *  @note It doesen't init SDL by itself, you need to launch
	 *  the methode run() of this class to display this instance in
	 *  your session.
	 * 
	 *  @param game_instance_name  (std::string) Name of game instance.
	 *  @param window_pos_x        (const int) Position of the window on the x axis.
	 *  @param window_pos_y        (const int) Position of the window on the y axis.
	 *  @param window_width        (const int) Width of the window.
	 *  @param window_height       (const int) Height of the window. 
	 */
	TorukiaEngine (const std::string game_instance_name, 
				const int window_pos_x,
				const int window_pos_y,
				const int window_width,
				const int window_height,
				const int32_t init_flags) :
				_game_instance_name(game_instance_name),
				m_window_pos_x(window_pos_x),
				m_window_pos_y(window_pos_y),
				m_window_width(window_width),
				m_window_height(window_height),
				_init_flags(init_flags),
				_context_flags(0),
				_user_flags(0),
				_quit(false)
	{

	}
	~TorukiaEngine() {}

	TorukiaEngine(const TorukiaEngine&) = delete;
	TorukiaEngine& operator=(const TorukiaEngine&) = delete;

	bool init_sdl();
	bool clean_sdl();
	/** @fn int TorukiaEngine::run(const int flags)
	 *  @bref run and display the game engine TorukiaEngine instance.
	 *  
	 *  Run the instance and display the instance object TorukiaEngine
	 *  and the user code logic.
	 *
	 * 	@param flags               (const int) Flags.
	 *  @return exit code, 0 for success, a negative number otherwise.
	 */
	int run(const int flags);
	/** @fn std::string game_instance_name() const
	 *  @bref Getter of int _game_instance_name.
	 *  
	 *  @return std::string internal name of instance.
	 */	
	std::string game_instance_name() const;
	/** @fn int init_flags() const
	 *  @bref Getter of int _init_flags.
	 *  
	 *  @return int of flags.
	 */
	int init_flags() const;
	/** @fn std::ostream get_init_flags_info()
	 *  @bref Return a std::ostream of information about the flags set.
	 *  
	 *  @return std::ostream of information about the flags set in plain text.
	 */
	std::string get_init_flags_info() const;
	/** @fn int context_flags() const
	 *  @bref Getter of int _context_flags.
	 *  
	 *  @return int of flags.
	 */	
	int context_flags() const;
	/** @fn std::ostream get_context_flags_info()
	 *  @bref Return a std::ostream of information about the flags set.
	 *  
	 *  @return std::ostream of information about the flags set in plain text.
	 */	
	std::string get_context_flags_info() const;
	/** @fn std::ostream get_all_info()
	 *  @bref Return a std::ostream of all information about the instance.
	 *  
	 *  @return std::ostream of information in plain text.
	 */
	std::string get_all_info() const;
};

std::ostream& operator<<(std::ostream& out, const TorukiaEngine& torukia_context) {
	out << torukia_context.get_all_info();
	return out;
}

class TorukiaEngineUnitTest : public TorukiaEngine {
public:
	TorukiaEngineUnitTest (const int window_pos_x,
				const int window_pos_y,
				const int window_width,
				const int window_height) :
				TorukiaEngine ("Test game", 
							window_pos_x,
							window_pos_y,
							window_width,
							window_height,
							2)
	{
	}

	bool run_tests(){
		bool global_success = true;
		unsigned int number_of_pass = 0;

		if( !test_init_flags_enum()) {
			global_success = false;
		} else {
			number_of_pass++;
		}

		if( !test_set_context_flags_raw_int()) {
			global_success = false;
		} else {
			number_of_pass++;
		}

		if( !test_set_context_flags_enum()) {
			global_success = false;
		} else {
			number_of_pass++;
		}

		if(global_success) {
			std::cout << "All test success ";
		} else {
			std::cout << "Test class failed ";
		}
		std::cout << "form 3 test, " << number_of_pass << " have passed." << std::endl;

		return global_success;
	}

	bool test_init_flags_enum() {
		if (_init_flags == TorukiaEngine::InitFlags::no_sound) {
			std::cout << "test_init_flags_raw_int passed, values of flags " 
			          << _init_flags
			          << std::endl;
			return true;
		}
		std::cout << "test_init_flags_raw_int failed, value of flags " 
		          << _init_flags
		          << std::endl;
		return false;
	}

	bool test_set_context_flags_raw_int() {
		set_context_flags((int32_t) 1);

		if (_context_flags == TorukiaEngine::ContextFlags::error_n_1) {
			std::cout << "test_set_context_flags_raw_int passed, values of flags " 
			          << _context_flags
			          << std::endl;
			return true;
		}
		std::cout << "test_set_context_flags_raw_int failed, value of flags " 
		          << _context_flags
		          << std::endl;
		return false;
	}

	bool test_set_context_flags_enum() {
		set_context_flags(TorukiaEngine::ContextFlags::error_user_code, true);
		set_context_flags(TorukiaEngine::ContextFlags::error_n_1, false);
		
		if (_context_flags == TorukiaEngine::ContextFlags::error_user_code) {
			std::cout << "test_set_context_flags_enum, values of flags " 
			          << _context_flags
			          << std::endl;
			return true;
		}
		std::cout << "test_set_context_flags_enum, value of flags " 
		          << _context_flags
		          << std::endl;
		return false;

	}
};
}
#endif /* TORUKIA_H */