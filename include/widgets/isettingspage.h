#pragma once

#include <QDialog>
#include <QGridLayout>
#include <QTabWidget>
#include <QWidget>

class SettingsWidget;

class SettingsWidget : public QWidget
{
  Q_OBJECT
public:
  SettingsWidget(QWidget* parent);

  QList<QWidget*> widgets();

  //  void addWidget(QWidget* widget,
  //                 int row,
  //                 int column,
  //                 Qt::Alignment alignment = Qt::Alignment())
  //  {
  //    m_widgets.append(widget);
  //    m_layout->addWidget(widget, row, column, alignment);
  //  }

  //  void addWidget(QWidget* widget,
  //                 int fromRow,
  //                 int fromColumn,
  //                 int rowSpan,
  //                 int columnSpan,
  //                 Qt::Alignment alignment = Qt::Alignment())
  //  {
  //    m_widgets.append(widget);
  //    m_layout->addWidget(
  //      widget, fromRow, fromColumn, rowSpan, columnSpan, alignment);
  //  }
  void addWidget(QWidget* widget) {
    m_widgets.append(widget);
  }

protected:
  QGridLayout* m_layout;
  QList<QWidget*> m_widgets;
};

class ISettingsDialog
{
public:
  virtual bool isModified() const = 0;
  virtual QList<SettingsWidget*> settingsPages() = 0;
  virtual void setSettingsPages(QList<SettingsWidget*> widgets) = 0;

protected:
  QList<SettingsWidget*> m_settingsPages;
};

//!

//! An extension of QTabWidget that is used to create setting/options
//! pages.
class SettingsTabWidget : public QTabWidget
{
  Q_OBJECT
public:
  //! Constructor for SettingsTabWidget
  SettingsTabWidget(QWidget* parent);

  //! Returns the SettingsWidget at index.
  SettingsWidget* widget(int index) const;
};
