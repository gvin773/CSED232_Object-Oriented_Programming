#ifndef TIMETABLEWINDOW_H
#define TIMETABLEWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QTimeEdit>
#include <QCheckBox>
#include <QFileDialog>
#include "subject.h"

enum Mode { NavigationMode, AddingMode, EditingMode }; //모드정보 enum

class TimetableWindow : public QMainWindow
{
    Q_OBJECT

public:
    TimetableWindow(QWidget *parent = nullptr);

    void addSubject(); //과목추가
    void editSubject(); //과목수정
    void submitSubject(); //리스트에 새롭게 만들어진 또는 수정된 과목 추가
    void cancel(); //취소
    void removeSubject(); //과목삭제
    void next(); //오른쪽이동
    void previous(); //왼쪽이동

private:
    QLineEdit *nameEdit;
    QLineEdit *locationEdit;
    QTimeEdit *startTimeEdit;
    QTimeEdit *endTimeEdit;
    QCheckBox *monCheck;
    QCheckBox *tueCheck;
    QCheckBox *wedCheck;
    QCheckBox *thuCheck;
    QCheckBox *friCheck;

    QGridLayout *mainLayout;
    QWidget *centralWidget;

    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QPushButton *removeButton;
    QPushButton *nextButton;
    QPushButton *previousButton;

    Mode currentMode;
    QVector<Subject> subjects;
    Subject oldSubject;

    void setEnable(bool enable); //모든입력칸 활성화/비활성화
    void storeInput(Subject& subject); //현재입력되어있는값저장
    void clearInput(); //모든입력칸값초기화
    void restoreInput(const Subject& subject); //subject값들을입력칸에삽입
    void updateInterface(Mode mode); //모드에 따라 입력칸 활성화/비활성화
    int findSubjectIndex(const QString& name) const; //name이라는 이름의 과목의 index를 리턴
};
#endif // TIMETABLEWINDOW_H
