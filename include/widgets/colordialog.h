#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QTabWidget>
#include <QDialog>
#include <QWidget>
#include <QMenu>
#include <QGridLayout>
#include <QColorDialog>
#include <QDialogButtonBox>
#include <QFrame>
#include <QLabel>
#include <QTableWidget>
#include <QTableView>
#include <QHeaderView>
#include <QAbstractTableModel>
#include <QMouseEvent>

// These are declared in the cpp file as they are just internal classes.
class ColorDisplay;
class ColorDragModel;
struct ColorDragData;
class ColorTable;

class ColorDisplay : public QFrame
{
  Q_OBJECT
  //  enum Side
  //  {
  //    Left,  //!< The left hand (primary) side is specified
  //    Right, //!< The right hand (secondary) side is specified
  //  };

public:
  ColorDisplay(const QColor& textColor,
                   const QColor& backgroundColor,
                   QWidget* parent = nullptr);

  void setBackgroundColor(const QColor& color, const QString& name);
  void setTextColor(const QColor& color, const QString& name);

  static const QString DISPLAYLABEL;
  static const QString DISPLAYBORDER;

  QColor backgroundColor() const;
  QString backgroundName() const;
  QColor textColor() const;
  QString textName() const;

signals:
  void backgroundColorChanged(const QColor& color, const QString& name);
  void textColorChanged(const QColor& color, const QString& name);

protected:

private:
  QLabel* m_label;
  QColor m_backColor;
  QColor m_textColor;
  QString m_backName;
  QString m_textName;
  bool m_colorSet, m_dropColorSet;

  QString calculateTextString();
  QString colorToStyle();
};

class ColorModel : public QAbstractTableModel
{
  Q_OBJECT

  struct Data
  {
    Data(const QString& n, const QColor& f, const QColor& b)
      : name(n)
      , fore(f)
      , back(b)
    {}
    QString name;
    QColor fore;
    QColor back;
  };
  typedef Data* Row;
  typedef Row* Column;

public:
  ColorModel(int rows, int columns);
  ~ColorModel();

  Qt::ItemFlags flags(const QModelIndex& index) const override;
  int rowCount(const QModelIndex& = QModelIndex()) const override;
  int columnCount(const QModelIndex& = QModelIndex()) const override;
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;
  QVariant headerData(int,
                      Qt::Orientation,
                      int = Qt::DisplayRole) const override;
  void setColorData(int row,
                    int column,
                    const QString& name,
                    const QColor& back,
                    const QColor& fore);
  QModelIndex index(int row,
                    int column,
                    const QModelIndex& = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex&) const override;

private:
  Column* m_data;
  int m_rows = 0;
  int m_columns = 0;
};

struct ColorDragData
{
  int r;
  int g;
  int b;
  QString name;
};

QDataStream&
operator<<(QDataStream& out, const ColorDragData& a);
QDataStream&
operator>>(QDataStream& in, ColorDragData& a);

class ColorTable : public QTableView
{
  Q_OBJECT
public:
  ColorTable(int rows, int columns, QWidget* parent = nullptr);

  QString name(const QModelIndex& index);
  QColor foreground(const QModelIndex& index);
  QColor background(const QModelIndex& index);
  void setData(int row, int column, bool x11, const QString& back);

protected:

private:
  QColor m_color;
  QString m_name;
  ColorModel* m_model;
  QSize m_size;
  QPixmap m_pixmap;
};

class ColorDialog : public QDialog
{
  Q_OBJECT
public:
  ColorDialog(QColor foreground, QColor background, QWidget* parent=nullptr);
  ColorDialog(const QString& foreground, const QString& background, QWidget* parent=nullptr);

protected:
  QTabWidget* m_tabs;
  QColor m_foreground;
  QColor m_background;
  QString m_foregroundName;
  QString m_backgroundName;
  QColorDialog* m_colorDlg;
  ColorDisplay* m_display;

  void initGui();
  void acceptChanges();
  QSize sizeHint() const;
  ColorTable* initSvgBlueGreen();
//  ColorTable* initSvgGreen();
  ColorTable* initSvgRedYellowBrown();
  ColorTable* initX11BlueGreen();
  ColorTable* initX11Red();
  ColorTable* initX11YellowBrown();
  ColorTable* initX11MonoFrame();
  QDialogButtonBox* createBtnBox();
  ColorDisplay* createColorDisplay();
  ColorTable* createColorTable(int columns = 7);
  void dialogColorHasChanged(const QColor& color);
  void colorClicked(const QModelIndex& index);
  void customMenuRequested(QPoint pos);

};

#endif // COLORDIALOG_H
