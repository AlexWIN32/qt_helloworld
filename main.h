/*******************************************************************************
    Author: Alexey Frolov (alexwin32@mail.ru)

    This software is distributed freely under the terms of the MIT License.
    See "LICENSE" or "http://copyfree.org/content/standard/licenses/mit/license.txt".
*******************************************************************************/

#ifndef MAIN_HEADER_
#define MAIN_HEADER_

#include <QtCore>
#include <QtGui>
//#include <X11/Xlib.h>
#if QT_VERSION > QT_VERSION_CHECK(5, 0, 0)
#include <QtWidgets>
#include <QApplication>
#endif

class TestDialog : public QDialog
{
    Q_OBJECT
private:
    QLineEdit *nameLine, *serverLine, *portLine;
    QPushButton *okButton, *cancelButton;
private Q_SLOTS:
    void apply();
public:
    TestDialog();
};

class MainWindow : public QWidget
{
    Q_OBJECT
private Q_SLOTS:
    void ShowDialog();
    void OnAppFocusChanged();
private:
    QPushButton *sendButton;
public:
    MainWindow(QWidget *parent = 0);
    
    //virtual void changeEvent(QEvent *event) override;
    //virtual void windowActivationChange(bool state) override;
    //virtual bool x11Event(XEvent * event) override;
    //virtual void focusInEvent ( QFocusEvent * event ) override;
    //virtual void focusOutEvent ( QFocusEvent * event ) override;
};

class Application final: public QApplication
{
public:
    using QApplication::QApplication;
    virtual bool eventFilter(QObject *object, QEvent *event) override;
    //virtual bool event( QEvent * pEvent ) override;
};

#endif
