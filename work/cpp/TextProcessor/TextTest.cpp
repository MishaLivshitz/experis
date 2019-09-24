#include "mu_test.h"
#include "TextProcessor.h"
#include "TextUpCaser.h"
#include "TextCensor.h"
#include "TextUpCensor.h"

void SendMessage(TextProcessor *_t)
{
    std::string userStr;
    std::cout << "Start writing, insert 'q' to quit" << std::endl;
    while(true)
    {
        getline(std::cin, userStr);

        if(userStr == "q")
        {
            break;
        }

        _t->process(userStr);
    }

    std::cout << "You have " << _t->numLinesProcessed() << " lines that has been processed" << std::endl;
    _t->display(std::cout);

    delete _t;

}

UNIT(TextUpCensor_test)

    TextProcessor *t = new TextUpCensor("abget");
    
    SendMessage(t);


END_UNIT

UNIT(TextCensor_test)

    TextProcessor *t = new TextCensor("abget");
    
    SendMessage(t);


END_UNIT

UNIT(TextProcessor_test)

    TextProcessor *t = new TextProcessor;
    
    SendMessage(t);


END_UNIT

UNIT(TextUpCaser_test)

    TextProcessor *t = new TextUpCaser;
    
    SendMessage(t);

END_UNIT


TEST_SUITE(Text processor test)

    TEST(TextUpCensor_test)
    TEST(TextProcessor_test)
    TEST(TextCensor_test)
    TEST(TextUpCaser_test)


END_SUITE
