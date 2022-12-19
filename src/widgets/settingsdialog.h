#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QPushButton>

#include "SMLibraries/widgets/isettingspage.h"

class SettingsDialog : public QDialog
{
  Q_OBJECT
public:
  SettingsDialog(QWidget *parent);

  int addTab(ISettingsDialog *parentWidget, const QString& label);
  int addTab(ISettingsDialog *parentWidget, const QIcon& icon, const QString& label);
  int insertTab(int index, ISettingsDialog *parentWidget, const QString& label);
  int insertTab(int index,
                ISettingsDialog* parentWidget,
                const QIcon& icon,
                const QString& label);
  bool 	isTabEnabled(int index) const;
  bool 	isTabVisible(int index) const;
  void 	removeTab(int index);

  void acceptChanges();
  void applyChanges();
  void cancelChanges();
  void help();

  int count();
  SettingsWidget* widget(int index);

signals:
  void apply();

protected:
  QSize sizeHint() const override;

private:
  SettingsTabWidget* m_tabs;


};

#endif // SETTINGSDIALOG_H
