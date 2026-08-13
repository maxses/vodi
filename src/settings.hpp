#ifndef SETTINGS_HPP
#define SETTINGS_HPP
/**---------------------------------------------------------------------------
 *
 * @file    settings.hpp
 * @brief   Map QSettings to widgets
 *
 * When an widget get changed (e.g. set an checkbox), save() has to be called.
 * The signal "signalSettingsChanged" gets emited which can be used by sheets
 * to update calculations.
 *
 * @date   20260813
 * @author Maximilian Seesslen <src@seesslen.net>
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <QSettings>
#include <QDoubleSpinBox>
#include <QTextEdit>
#include <QVariant>
#include <QCheckBox>
#include <QComboBox>


/*--- Declarations ---------------------------------------------------------*/


enum class EType
{
   EDouble,
   EText,
   EBoolean,
   EIndex,
};

struct SMapEntry
{
   const char* name;
   QObject *widget;
   EType type;
   QVariant _default;
};

class CSettings : public QSettings //, public QObject
{
   Q_OBJECT

   QList<SMapEntry> m_mapList;

public:

signals:
   void signalSettingsChanged();

public:
   CSettings(){};
   ~CSettings(){};

   static void setText( QObject *widget, const char *name, const QString &value )
   {
      QTextEdit *textEdit=dynamic_cast<QTextEdit *>( widget );
      if( !textEdit )
      {
         qWarning("Wrong widget type for '%s'", name);
         return;
      }
      textEdit->setText( value );
   }

   void load()
   {
      for( const SMapEntry &e: m_mapList )
      {
         switch(e.type)
         {
            case EType::EDouble:
            {
               QDoubleSpinBox *spinBox=dynamic_cast<QDoubleSpinBox *>( e.widget );
               if( !spinBox )
               {
                  qWarning("Wrong widget type for '%s'", e.name);
                  break;
               }
               spinBox->setValue( value( e.name ).toDouble() );
               break;
            }
         case EType::EText:
         {
            QTextEdit *textEdit=dynamic_cast<QTextEdit *>( e.widget );
            if( !textEdit )
            {
               qWarning("Wrong widget type for '%s'", e.name);
               break;
            }
            textEdit->setText( value( e.name ).toString() );
            break;
         }
         case EType::EBoolean:
         {
            QCheckBox *checkBox=dynamic_cast<QCheckBox *>( e.widget );
            if( !checkBox )
            {
               qWarning("Wrong widget type for '%s'", e.name);
               break;
            }
            checkBox->setChecked( value( e.name ).toBool() );
            break;
         }
         case EType::EIndex:
         {
            QComboBox *comboBox=dynamic_cast<QComboBox *>( e.widget );
            if( !comboBox )
            {
               qWarning("Wrong widget type for '%s'", e.name);
               break;
            }
            comboBox->setCurrentIndex( value( e.name ).toInt() );
            break;
         }
         default:
            qWarning("Unhandled data type: %d", (int)e.type);
            break;
         }
      }
   };
   void saveText(QObject *widget, const char* name)
   {
      QTextEdit *textEdit=dynamic_cast<QTextEdit *>( widget );
      if( !textEdit )
      {
         qWarning("Wrong widget type for '%s'", name);
         return;
      }
      setValue( name, textEdit->toHtml() );
      return;
   }
   void saveBool(QObject *widget, const char* name)
   {
      QCheckBox *checkBox=dynamic_cast<QCheckBox *>( widget );
      if( !checkBox )
      {
         qWarning("Wrong widget type for '%s'", name);
         return;
      }
      setValue( name, checkBox->isChecked() );
      return;
   }

   void saveIndex(QObject *widget, const char* name)
   {
      QComboBox *comboBox=dynamic_cast<QComboBox *>( widget );
      if( !comboBox )
      {
         qWarning("Wrong widget type for '%s'", name);
         return;
      }
      setValue( name, comboBox->currentIndex() );
      return;
   }

   void save()
   {
      for( const SMapEntry &e: m_mapList )
      {
         switch(e.type)
         {
            case EType::EDouble:
            {
               QDoubleSpinBox *spinBox=dynamic_cast<QDoubleSpinBox *>( e.widget );
               if( !spinBox )
               {
                  qWarning("Wrong widget type for '%s'", e.name);
                  break;
               }
               setValue( e.name, spinBox->value() );
               break;
            }
            case EType::EText:
            {
               saveText( e.widget, e.name );
               break;
            }
            case EType::EBoolean:
            {
               saveBool( e.widget, e.name );
               break;
            }
            case EType::EIndex:
            {
               saveIndex( e.widget, e.name );
               break;
            }
            default:
            {
               qWarning("Unhandled data type: %d", (int)e.type);
               break;
            }
         }
      }

      emit( signalSettingsChanged() );
   };

   static void setDouble( QObject *widget, const char *name, double value)
   {
      QDoubleSpinBox *spinBox=dynamic_cast<QDoubleSpinBox *>( widget );
      if( !spinBox )
      {
         qWarning("Wrong widget type for '%s'", name);
         return;
      }
      spinBox->setValue( value );
   }
   
   static void setBool( QObject *widget, const char *name, bool value)
   {
      QCheckBox *checkBox=dynamic_cast<QCheckBox *>( widget );
      if( !checkBox )
      {
         qWarning("Wrong widget type for '%s'", name);
         return;
      }
      checkBox->setChecked( value );
   }
   
   void reset()
   {
      for( const SMapEntry &e: m_mapList )
      {
         switch(e.type)
         {
            case EType::EDouble:
            {
               setDouble( e.widget, e.name, e._default.toDouble() );
               break;
            }
            case EType::EText:
            {
               setText( e.widget, e.name, e._default.toString() );
               break;
            }
            case EType::EBoolean:
            {
               setBool( e.widget, e.name, e._default.toBool() );
               break;
            }
            default:
               qWarning("Unhandled data type: %d", (int)e.type);
               break;
         }
      }
   };
   void append(const QList<SMapEntry> list )
   {
      m_mapList+=list;
   }

private:

//private slots:
//   void slotQuit();

};


/*--- Fin ------------------------------------------------------------------*/
#endif // SETTINGS_HPP
