//
// Created by wurmel on 23/05/17.
//

#ifndef CPP_INDIE_STUDIO_AEVENTREGISTER_HH
#define CPP_INDIE_STUDIO_AEVENTREGISTER_HH

# include <OIS/OIS.h>

namespace Indie
{
    class AEventRegister : public OIS::KeyListener {
    public:
        virtual ~AEventRegister() {}

        virtual void registerKeyboardEvent(OIS::Keyboard *) = 0;
        virtual void registerMouseEvent(OIS::Mouse *) = 0;
        virtual bool keyPressed(const OIS::KeyEvent& ke) = 0;
        virtual bool keyReleased(const OIS::KeyEvent& ke) = 0;
    };
}

#endif //CPP_INDIE_STUDIO_AEVENTREGISTER_HH
