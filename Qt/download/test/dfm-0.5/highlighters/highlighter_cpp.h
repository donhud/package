#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H
#include <QSyntaxHighlighter>

 #include <QHash>
 #include <QTextCharFormat>

 class QTextDocument;

 class HighlighterCpp : public QSyntaxHighlighter
 {
     Q_OBJECT

 public:
     HighlighterCpp(QTextDocument *parent = 0);

 protected:
     void highlightBlock(const QString &text);

 private:
     struct HighlightingRule
     {
         QRegExp pattern;
         QTextCharFormat format;
     };
     QVector<HighlightingRule> highlightingRules;

     QRegExp commentStartExpression;
     QRegExp commentEndExpression;

     QTextCharFormat keywordFormat;
     QTextCharFormat classFormat;
     QTextCharFormat singleLineCommentFormat;
     QTextCharFormat multiLineCommentFormat;
     QTextCharFormat quotationFormat;
     QTextCharFormat functionFormat;
     QTextCharFormat typeFormat;
 };
#endif // HIGHLIGHTER_H
