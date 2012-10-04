#ifndef STATELOOPIFC_H_INCLUDED
#define STATELOOPIFC_H_INCLUDED

#include <GL/freeglut.h>
#include "StateMachine.h"

class StateLoopIFC
{
    public:
        StateLoopIFC(StateMachine* stateMachine) { this->stateMachine = stateMachine; }

        virtual void display()
        {
            glClear( GL_COLOR_BUFFER_BIT );
            glutSwapBuffers();
        }

        virtual void update(int value) = 0;

        virtual void mouseButton(int button, int state, int x, int y) { }
        virtual void clickDrag(int x, int y) { }
        virtual void mouseMove(int x, int y) { }
        virtual void reshape(int width, int height) { }

        virtual void key(unsigned char key, int x, int y)
        {
            switch (key)
            {
                case 27: exit(0);
                default: break;
            }
        }

        virtual void specialUp(int key, int x, int y)
        {
            switch(key) {
                case GLUT_KEY_RIGHT : stateMachine->setArrowState(RIGHT, false); break;
                case GLUT_KEY_LEFT :  stateMachine->setArrowState(LEFT , false);break;
                case GLUT_KEY_UP :    stateMachine->setArrowState(UP   , false); break;
                case GLUT_KEY_DOWN :  stateMachine->setArrowState(DOWN , false); break;
                default: break;
            }
        }

        virtual void specialDown(int key, int x, int y)
        {
            switch(key) {
                case GLUT_KEY_RIGHT : stateMachine->setArrowState(RIGHT, true); break;
                case GLUT_KEY_LEFT :  stateMachine->setArrowState(LEFT , true);break;
                case GLUT_KEY_UP :    stateMachine->setArrowState(UP   , true); break;
                case GLUT_KEY_DOWN :  stateMachine->setArrowState(DOWN , true); break;
                break;
            }
        }

        virtual void assumeControl(StateLoopIFC*& currentActor)
        {
            std::cout << "--- UNKOWN ACTOR IS ASSUMING CONRTOL OF GLUT MAIN LOOP ---\n";
            currentActor = this;
        }

    protected:
        StateMachine* stateMachine;
};

#endif // STATELOOPIFC_H_INCLUDED
