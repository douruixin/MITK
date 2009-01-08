/*=========================================================================

 Program:   openCherry Platform
 Language:  C++
 Date:      $Date$
 Version:   $Revision$

 Copyright (c) German Cancer Research Center, Division of Medical and
 Biological Informatics. All rights reserved.
 See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notices for more information.

 =========================================================================*/

#include "cherryQtControlWidget.h"

#include <cherryShell.h>

#include <QMoveEvent>
#include <QResizeEvent>

#include <algorithm>

namespace cherry {

QtControlWidget::QtControlWidget(QWidget* parent, Shell::Pointer shell, Qt::WindowFlags f)
 : QFrame(parent, f)
{
  this->setFrameStyle(QFrame::NoFrame);

  controller = new QtWidgetController(shell);

  // TODO WeakPointer: QVariant should hold a weak pointer
  QVariant variant(QVariant::UserType);
  variant.setValue(controller);
  this->setProperty(QtWidgetController::PROPERTY_ID, variant);
}

QtControlWidget::~QtControlWidget()
{
  std::cout << "DELETING control widget: " << qPrintable(this->objectName()) << std::endl;
}

void QtControlWidget::changeEvent(QEvent* event)
{
  typedef IShellListener::Events::ShellEventType::ListenerList ListenerList;
  ShellEvent::Pointer shellEvent(new ShellEvent(controller->shell));
  switch (event->type())
  {
  case QEvent::WindowActivate:
  {
    ListenerList activatedListeners(controller->shellEvents.shellActivated.GetListeners());
    for (ListenerList::iterator listener = activatedListeners.begin();
         listener != activatedListeners.end(); ++listener)
    {
      (*listener)->Execute(shellEvent);
      if (!shellEvent->doit) {
        event->accept();
        return;
      }
    }
  }
    break;
  case QEvent::WindowDeactivate:
  {
    ListenerList deactivatedListeners(controller->shellEvents.shellDeactivated.GetListeners());
    for (ListenerList::iterator listener = deactivatedListeners.begin();
         listener != deactivatedListeners.end(); ++listener)
    {
      (*listener)->Execute(shellEvent);
      if (!shellEvent->doit) {
        event->accept();
        return;
      }
    }
  }
    break;
  case QEvent::WindowStateChange:
  {
    QWindowStateChangeEvent* stateEvent = dynamic_cast<QWindowStateChangeEvent*>(event);
    Qt::WindowStates oldState = stateEvent->oldState();
    if (this->isMinimized() && !(oldState & Qt::WindowMinimized))
    {
      ListenerList iconifiedListeners(controller->shellEvents.shellIconified.GetListeners());
      for (ListenerList::iterator listener = iconifiedListeners.begin();
         listener != iconifiedListeners.end(); ++listener)
      {
        (*listener)->Execute(shellEvent);
        if (!shellEvent->doit) {
          event->accept();
          return;
        }
      }
    }
    else if (oldState & Qt::WindowMinimized && !this->isMinimized())
    {
      ListenerList deiconifiedListeners(controller->shellEvents.shellDeiconified.GetListeners());
      for (ListenerList::iterator listener = deiconifiedListeners.begin();
         listener != deiconifiedListeners.end(); ++listener)
      {
        (*listener)->Execute(shellEvent);
        if (!shellEvent->doit) return;
      }
    }
  }
    break;
  default:
    break;
  }

  QFrame::changeEvent(event);
}

void QtControlWidget::closeEvent(QCloseEvent* event)
{
  typedef IShellListener::Events::ShellEventType::ListenerList ListenerList;

  ShellEvent::Pointer shellEvent(new ShellEvent(controller->shell));

  ListenerList closedListeners(controller->shellEvents.shellClosed.GetListeners());
  for (ListenerList::iterator listener = closedListeners.begin();
       listener != closedListeners.end(); ++listener)
  {
    (*listener)->Execute(shellEvent);
    if (!shellEvent->doit) {
      event->accept();
      return;
    }
  }

  QFrame::closeEvent(event);
}

void QtControlWidget::moveEvent(QMoveEvent* event)
{
  GuiTk::ControlEvent::Pointer controlEvent(new GuiTk::ControlEvent(static_cast<QWidget*>(this), event->pos().x(), event->pos().y()));
  controller->controlEvents.movedEvent(controlEvent);
}

void QtControlWidget::resizeEvent(QResizeEvent* event)
{
  GuiTk::ControlEvent::Pointer controlEvent(new GuiTk::ControlEvent(static_cast<QWidget*>(this), 0, 0, event->size().width(), event->size().height()));
  controller->controlEvents.resizedEvent(controlEvent);
}

void QtControlWidget::inFocusEvent(QFocusEvent* /*event*/)
{
  GuiTk::ControlEvent::Pointer controlEvent(new GuiTk::ControlEvent(static_cast<QWidget*>(this)));
  controller->controlEvents.activatedEvent(controlEvent);
}

}
