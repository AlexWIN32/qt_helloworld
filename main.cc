/*******************************************************************************
    Author: Alexey Frolov (alexwin32@mail.ru)

    This software is distributed freely under the terms of the MIT License.
    See "LICENSE" or "http://copyfree.org/content/standard/licenses/mit/license.txt".
*******************************************************************************/

#include "main.h"
#include <iostream>
//#include <X11/Xlib.h>
#include <thread>
#include <unistd.h>

TestDialog::TestDialog()
{
    nameLine = new QLineEdit();
    serverLine = new QLineEdit();
    portLine = new QLineEdit();

    QGridLayout *serverLayout = new QGridLayout;
    serverLayout->addWidget(new QLabel(tr("Server")), 0, 0);
    serverLayout->addWidget(serverLine, 0, 1);
    serverLayout->addWidget(new QLabel(tr("Port")), 0, 2);
    serverLayout->addWidget(portLine, 0, 3);

    QGridLayout *nameLayout = new QGridLayout;
    nameLayout->addWidget(new QLabel(tr("Name")), 0, 0, Qt::AlignRight);
    nameLayout->addWidget(nameLine, 0, 1);

    okButton = new QPushButton(tr("OK"));
    cancelButton = new QPushButton(tr("Cancel"));

    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(apply()));

    QGridLayout *btnLayout = new QGridLayout;
    btnLayout->addWidget(okButton, 0, 0, Qt::AlignRight);
    btnLayout->addWidget(cancelButton, 0, 1, Qt::AlignLeft);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addLayout(serverLayout, 0, 0);
    mainLayout->addLayout(nameLayout, 1, 0);
    mainLayout->addLayout(btnLayout, 2, 0);

    setLayout(mainLayout);
    setWindowTitle(tr("Options"));
}

void TestDialog::apply()
{
    close();
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    sendButton = new QPushButton(tr("Show dialog"));

    connect(sendButton, SIGNAL(clicked()), this, SLOT(ShowDialog()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(sendButton, 0, 0);

    setLayout(mainLayout);
    setWindowTitle(tr("Test"));
}

void MainWindow::ShowDialog()
{
    TestDialog tstDlg;
    tstDlg.setModal(true);
    tstDlg.exec();        
}

void MainWindow::OnAppFocusChanged()
{
    std::cout << "Focus changed singnal" << std::endl;
    
}

/*
void MainWindow::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);

    if (event->type() == QEvent::ActivationChange)
    {
        if(isActiveWindow())
        {
            std::cout << "AAA focus in " << std::endl;
        }
        else
        {
            std::cout << "AAA focus out " << std::endl;    
        }
    }
}

void MainWindow::windowActivationChange(bool state)
{    
    QWidget::windowActivationChange(state);
    
    if(state)
    {
        std::cout << "AAA windowActivationChange(true) " << std::endl;
    }
    else
    {
        std::cout << "AAA windowActivationChange(false) " << std::endl;    
    }
    
}

bool MainWindow::x11Event(XEvent * event)
{
    if(event->type == FocusIn)
       std::cout << "AAA X11 focus in " << std::endl;
    else if(event->type == FocusOut)
        std::cout << "AAA X11 focus out " << std::endl;
        
    return QWidget::x11Event(event);
}

void MainWindow::focusInEvent ( QFocusEvent * event )
{
    QWidget::focusInEvent(event);
    std::cout << "AAA focus in " << std::endl;
}

void MainWindow::focusOutEvent ( QFocusEvent * event )
{
    QWidget::focusInEvent(event);
    std::cout << "AAA focus out " << std::endl;    
}

bool Application::event( QEvent * event )
{
    if ( event->type() == QEvent::ApplicationActivate )
        std::cout << "AAA Application focus in " << std::endl;
    else if ( event->type() == QEvent::ApplicationDeactivate )
        std::cout << "AAA Application focus out " << std::endl;
}
*/

bool Application::eventFilter(QObject *object, QEvent *event)
{
    if ( event->type() == QEvent::ApplicationActivate )
        std::cout << "AAA ApplicationActivate " << std::endl;
    else if ( event->type() == QEvent::ApplicationDeactivate )
        std::cout << "AAA ApplicationDeactivate " << std::endl;
    /*
    if (event->type() == QEvent::FocusIn)
    {    
         std::cout << "AAA app focus in " << std::endl;
    }
    else if (event->type() == QEvent::FocusOut)
    {    
        std::cout << "AAA app  focus in " << std::endl;
    }
    */
    return QApplication::eventFilter(object, event);
}


int main(int argc, char* argv[])
{
    Application app(argc, argv);
    app.installEventFilter(&app);
    
    MainWindow window;
    
    QWidget::connect(&app, SIGNAL(focusChanged(QWidget*, QWidget*)), &window, SLOT(OnAppFocusChanged()));
    
    window.show();
    window.setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            window.size(),
            app.desktop()->availableGeometry()
        )
    );
      
    /*
    std::thread thr(
        [&]()
        {
            
            while (true)
            {
                usleep(1000000);
                
                bool a = true;
                
                if( QApplication::focusWidget() == &window) 
                {
                
                    a = true; 
                    
                    std::cout << "AAA focus in " << std::endl;
                }
                else
                {
                    a = false; 
                    
                    std::cout << "AAA focus out " << std::endl;
                    
                }                
                
            }
        }
    );
    */
    
    
    app.exec();    
    
    //thr.join();
    return 0;
}

