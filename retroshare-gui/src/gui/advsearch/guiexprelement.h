/****************************************************************
*  RetroShare is distributed under the following license:
*
*  Copyright (C) 2006, 2007 The RetroShare Team
*
*  This program is free software; you can redistribute it and/or
*  modify it under the terms of the GNU General Public License
*  as published by the Free Software Foundation; either version 2
*  of the License, or (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, 
*  Boston, MA  02110-1301, USA.
****************************************************************/
#ifndef _GuiExprElement_h_
#define _GuiExprElement_h_

#include <QWidget>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QComboBox>
#include <QCheckBox>
#include <QVariant>
#include <QLineEdit>
#include <QDateEdit>
#include <QLabel>
#include <QRegExp>
#include <QRegExpValidator>
#include <QHBoxLayout>
#include <QMap>

#include <iostream>

#include <retroshare/rsexpr.h>

enum ExprSearchType
{
    NameSearch,
    PathSearch,
    ExtSearch,
    HashSearch,
    DateSearch,
    SizeSearch,
    PopSearch

};

class GuiExprElement: public QWidget
{
    Q_OBJECT

public:
    GuiExprElement(QWidget * parent = 0);
    virtual void adjustForSearchType(ExprSearchType) {}
    virtual ~GuiExprElement(){}
    virtual void set(int){}
    virtual void set(QObject*){}
    bool isStringSearchExpression();

/* indices for possible cb options */ 
    static const int AND_INDEX;
    static const int XOR_INDEX;
    static const int OR_INDEX;
    static const int NAME_INDEX;
    static const int PATH_INDEX;
    static const int EXT_INDEX;
    static const int HASH_INDEX;
    static const int KEYWORDS_INDEX;
    static const int COMMENTS_INDEX;
    static const int META_INDEX;
    static const int DATE_INDEX;
    static const int SIZE_INDEX;
    static const int POP_INDEX;

    static const int CONTAINS_INDEX;
    static const int CONTALL_INDEX;
    static const int IS_INDEX;

    static const int LT_INDEX;
    static const int LTE_INDEX;
    static const int EQUAL_INDEX;
    static const int GTE_INDEX;
    static const int GT_INDEX;
    static const int RANGE_INDEX;

    static QMap<int, ExprSearchType> TermsIndexMap;

    virtual QString toString(){return QString("");}
    
protected:
    /** prepare the option lists for use */
    void initialiseOptionsLists();

    /** provides the appropriate options list for the 
        condition combobox */
    QStringList getConditionOptions(ExprSearchType t);
    
    QHBoxLayout* createLayout(QWidget* parent = 0);
    QFrame * internalframe;

    ExprSearchType searchType;

    static bool initialised;
    static QStringList exprOpsList;
    static QStringList searchTermsOptionsList;
    static QStringList stringOptionsList;
    static QStringList relOptionsList;

    // provides a mapping of condition operators to RSExpr reloperators
    static QMap<int, LogicalOperator> logicalOpIndexMap;
    static QMap<int, StringOperator>  strConditionIndexMap;
    static QMap<int, RelOperator>     relConditionIndexMap;

    // provides a mapping of indexes to translatable strings
    static QMap<int, QString> logicalOpStrMap;
    static QMap<int, QString> termsStrMap;
    static QMap<int, QString> strConditionStrMap;
    static QMap<int, QString> relConditionStrMap;


};

/** the Expression operator combobox element */
class ExprOpElement : public GuiExprElement
{
    Q_OBJECT
    
public:
    ExprOpElement(QWidget * parent = 0);
    LogicalOperator getLogicalOperator();
    QString toString();
private:
    QComboBox * cb;
};

/** the Terms combobox element */
class ExprTermsElement : public GuiExprElement
{
    Q_OBJECT
    
public:
    ExprTermsElement(QWidget * parent = 0);
    int getTermsIndex();
    RelOperator getRelOperator();
    StringOperator getStringOperator();
    void set(int i) {cb->setCurrentIndex(i);}
    QString toString();

signals:
    void currentIndexChanged(int);

private:
    QComboBox * cb;
};

/** the Conditions combobox element */
class ExprConditionElement : public GuiExprElement
{
    Q_OBJECT
    
public:
    ExprConditionElement(ExprSearchType, QWidget * parent = 0);
    RelOperator getRelOperator();
    StringOperator getStringOperator();
    void adjustForSearchType(ExprSearchType);
    void set(int i) {cb->setCurrentIndex(i);}
    QString toString();

signals:
    void currentIndexChanged(int);

private:
    QComboBox * cb;
};

/** the Parameter element */
class ExprParamElement : public GuiExprElement
{
    Q_OBJECT
    
public:
    ExprParamElement(ExprSearchType, QWidget * parent = 0);
    QVariant* getRSExprValue();
    void adjustForSearchType(ExprSearchType);
    void setRangedSearch(bool ranged = true);
    bool ignoreCase();
    QString getStrSearchValue();
    uint64_t getIntValue();
    uint64_t getIntLowValue();
    uint64_t getIntHighValue();
    virtual QString toString();

private:
    QRegExpValidator * numValidator;
    QRegExpValidator * hexValidator;
    QFrame * rangeParamsFrame;
    bool inRangedConfig;
    uint64_t getIntValueFromField(QString fieldName, bool isToField=false,bool *ok = NULL);
};

#endif
