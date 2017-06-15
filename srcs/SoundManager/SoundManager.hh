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
        void    loadSound(std::string const&, bool loop = false);

    private:
        std::vector<std::unique_ptr<sf::Music> >    _musicList;
    };
}


#endif //CPP_INDIE_STUDIO_SOUNDMANAGER_HH
