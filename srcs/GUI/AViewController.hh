//
// Created by wurmel_a on 06/06/17.
//

#ifndef CPP_INDIE_STUDIO_VIEWCONTROLLER_HH
#define CPP_INDIE_STUDIO_VIEWCONTROLLER_HH

# include "../EventListener/AEventRegister.hh"

namespace Indie {
    class   RootViewController;

    class   AViewController : public AEventRegister {
    public:
        enum    ExitStatus {
            EXIT = 0,
            GO_ON = 1,
            GO_BACK
        };

    public:
        AViewController(RootViewController&);
        ~AViewController();

    public:
        virtual void    initView() = 0;
        virtual ExitStatus   updateView() = 0;
        virtual void    viewShouldDisapear();
        virtual void    viewShouldReapear();


    public:
        virtual bool    mouseMoved(const OIS::MouseEvent&);
        virtual bool    mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);
        virtual bool    mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);
        virtual bool    keyPressed(const OIS::KeyEvent&);
        virtual bool    keyReleased(const OIS::KeyEvent&);
        virtual void    registerKeyboardEvent(OIS::Keyboard *);
        virtual void    registerMouseEvent(OIS::Mouse *);

    protected:
        RootViewController& _delegate;
        ExitStatus _state;
    };
}

#endif //CPP_INDIE_STUDIO_VIEWCONTROLLER_HH
