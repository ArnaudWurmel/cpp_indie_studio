//
// Created by wurmel_a on 09/06/17.
//

#ifndef CPP_INDIE_STUDIO_SOUNDMANAGER_HH
#define CPP_INDIE_STUDIO_SOUNDMANAGER_HH

# include <SFML/Audio.hpp>

namespace Indie {
    class SoundManager {
    public:
        static SoundManager *getSingloton(bool reset = false);
    public:
        SoundManager();
        ~SoundManager();

    public:
        void    loadSound(std::string const&);

    private:
        sf::Music   *_currentMusic;
    };
}


#endif //CPP_INDIE_STUDIO_SOUNDMANAGER_HH
