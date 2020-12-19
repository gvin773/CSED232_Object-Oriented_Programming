#include "timetablewindow.h"

TimetableWindow::TimetableWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QLabel *nameLabel = new QLabel(tr("Subject:"));
    nameEdit = new QLineEdit;
    nameEdit->setReadOnly(true);

    QLabel *locationLabel = new QLabel(tr("Location:"));
    locationEdit = new QLineEdit;
    locationEdit->setReadOnly(true);

    QLabel *starttimeLabel = new QLabel(tr("Start Time:"));
    startTimeEdit = new QTimeEdit;
    startTimeEdit->setTime(QTime(12,00));
    startTimeEdit->setReadOnly(true);

    QLabel *endtimeLabel = new QLabel(tr("End Time:"));
    endTimeEdit = new QTimeEdit;
    endTimeEdit->setTime(QTime(12,00));
    endTimeEdit->setReadOnly(true);
    //이름,장소,수업시간에 사용할 한줄입력, 시간입력 다루는 객체 초기설정

    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    //에러방지용 centralWidget

    mainLayout = new QGridLayout(centralWidget);
    QVBoxLayout *editLayout1 = new QVBoxLayout;
    QVBoxLayout *editLayout2 = new QVBoxLayout;
    editLayout1->addWidget(nameLabel);
    editLayout2->addWidget(nameEdit);
    editLayout1->addWidget(locationLabel);
    editLayout2->addWidget(locationEdit);
    editLayout1->addWidget(starttimeLabel);
    editLayout2->addWidget(startTimeEdit);
    editLayout1->addWidget(endtimeLabel);
    editLayout2->addWidget(endTimeEdit);
    mainLayout->addLayout(editLayout1, 0, 0);
    mainLayout->addLayout(editLayout2, 0, 1);
    //각각 하나의 레이아웃에 합치고 메인레이아웃에 삽입

    setLayout(mainLayout);
    setWindowTitle(tr("Timetable"));

    monCheck = new QCheckBox("&Mon");
    monCheck->setEnabled(false);
    tueCheck = new QCheckBox("&Tue");
    tueCheck->setEnabled(false);
    wedCheck = new QCheckBox("&Wed");
    wedCheck->setEnabled(false);
    thuCheck = new QCheckBox("&Thu");
    thuCheck->setEnabled(false);
    friCheck = new QCheckBox("&Fri");
    friCheck->setEnabled(false);
    //체크박스 만들기

    QHBoxLayout *buttonLayout3 = new QHBoxLayout;
    buttonLayout3->addWidget(monCheck);
    buttonLayout3->addWidget(tueCheck);
    buttonLayout3->addWidget(wedCheck);
    buttonLayout3->addWidget(thuCheck);
    buttonLayout3->addWidget(friCheck);
    mainLayout->addLayout(buttonLayout3, 4, 1);
    //하나의 레이아웃에 합치고 메인레이아웃에 삽입

    addButton = new QPushButton(tr("&Add"));
    addButton->show();
    editButton = new QPushButton(tr("&Edit"));
    editButton->setEnabled(false);
    removeButton = new QPushButton(tr("&Remove"));
    removeButton->setEnabled(false);
    submitButton = new QPushButton(tr("&Submit"));
    submitButton->setEnabled(false);
    cancelButton = new QPushButton(tr("&Cancel"));
    cancelButton->setEnabled(false);
    //버튼 5개 생성

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(submitButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout, 0, 2);
    //하나의 레이아웃에 합치고 메인레이아웃에 삽입

    nextButton = new QPushButton(tr("&->"));
    nextButton->setEnabled(false);
    previousButton = new QPushButton(tr("&<-"));
    previousButton->setEnabled(false);
    //좌우 이동 버튼 생성

    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
    buttonLayout2->addWidget(previousButton);
    buttonLayout2->addWidget(nextButton);
    mainLayout->addLayout(buttonLayout2, 5, 1);
    //하나의 레이아웃에 합치고 메인레이아웃에 삽입

    connect(addButton, &QPushButton::clicked, this, &TimetableWindow::addSubject);
    connect(editButton, &QPushButton::clicked, this, &TimetableWindow::editSubject);
    connect(removeButton, &QPushButton::clicked, this, &TimetableWindow::removeSubject);
    connect(submitButton, &QPushButton::clicked, this, &TimetableWindow::submitSubject);
    connect(cancelButton, &QPushButton::clicked, this, &TimetableWindow::cancel);

    connect(nextButton, &QPushButton::clicked, this, &TimetableWindow::next);
    connect(previousButton, &QPushButton::clicked, this, &TimetableWindow::previous);
    //각 버튼과 각 버튼에 대응되는 함수 연결
}

void TimetableWindow::addSubject() //과목추가
{
    updateInterface(AddingMode);

    storeInput(oldSubject);
    clearInput();
}

void TimetableWindow::editSubject() //과목수정
{
    updateInterface(EditingMode);

    storeInput(oldSubject);
}

void TimetableWindow::submitSubject() //리스트에 새롭게 만들어진 또는 수정된 과목 추가
{
    Subject sub;
    storeInput(sub);

    if(sub.getName().isEmpty() || sub.getLocation().isEmpty()) //이름이나 장소가 비었으면
    {
        QMessageBox::information(this, tr("Empty Field"), tr("Please enter a name and location of subject."));
        return;
    }

    if(sub.getStartTime() > sub.getEndTime()) //시작시간이 더 늦으면
    {
        QMessageBox::information(this, tr("Submit Unsuccessful"), tr("End time should be later than start time."));
        return;
    }

    if(sub.getMon() == false && sub.getTue() == false && sub.getWed() == false && sub.getThu() == false && sub.getFri() == false) //체크된 요일이 없으면
    {
        QMessageBox::information(this, tr("Submit Unsuccessful"), tr("At least one day should be chosen for subject."));
        return;
    }

    if(currentMode == AddingMode)
    {
        if(findSubjectIndex(sub.getName()) == -1) //이름을 못찾았으면
        {
            subjects.push_back(sub);
            QMessageBox::information(this, tr("Add Successful"), tr("\"%1\" has been added to your timetable.").arg(sub.getName()));
        }
        else //찾았으면
        {
            QMessageBox::information(this, tr("Add Unsuccessful"), tr("Sorry, \"%1\" is already in your timetable.").arg(sub.getName()));
            return;
        }
    }

    else if(currentMode == EditingMode)
    {
        if(findSubjectIndex(sub.getName()) == -1 || sub.getName() == oldSubject.getName()) //이름을 못찾았거나, 지금 수정하고 있는 이름과 같으면
        {
            subjects.remove(findSubjectIndex(oldSubject.getName()));
            subjects.push_back(sub);            
            QMessageBox::information(this, tr("Edit Successful"), tr("\"%1\" has been edited in your timetable.").arg(sub.getName()));
        }

        else //이름을 찾았는데 지금 수정하고 있는 것의 원래 이름도 아니면
        {
            QMessageBox::information(this, tr("Edit Unsuccessful"), tr("Sorry, \"%1\" is already in your timetable.").arg(sub.getName()));
            return;
        }
    }

    updateInterface(NavigationMode);
}

void TimetableWindow::cancel() //취소
{
    restoreInput(oldSubject);
    updateInterface(NavigationMode);
}

void TimetableWindow::removeSubject() //과목삭제
{
    QString name = nameEdit->text();

    int button = QMessageBox::question(this, tr("Confirm Remove"), tr("Are you sure you want to remove \"%1\"?").arg(name), QMessageBox::Yes | QMessageBox::No);
    if(button == QMessageBox::Yes) //Yes를 클릭하면
    {
        previous();
        subjects.remove(findSubjectIndex(name));

        QMessageBox::information(this, tr("Remove Successful"), tr("\"%1\" has been removed from your timetable.").arg(name));
    }

    updateInterface(NavigationMode);
}

void TimetableWindow::next() //오른쪽이동
{
    QString name = nameEdit->text();
    int i = findSubjectIndex(name);

    if(i != subjects.size()) //오른쪽 끝이 아니면
        i++;

    if(i == subjects.size()) //오른쪽 끝이면
        i = 0;

    restoreInput(subjects[i]);
}

void TimetableWindow::previous() //왼쪽이동
{
    QString name = nameEdit->text();
    int i = findSubjectIndex(name);

    if(i == 0) i = subjects.size()-1; //왼쪽 끝이면
    else i--; //왼쪽끝이 아니면

    restoreInput(subjects[i]);
}

void TimetableWindow::setEnable(bool enable) //모든입력칸 활성화/비활성화
{
    nameEdit->setReadOnly(!enable);
    locationEdit->setReadOnly(!enable);
    startTimeEdit->setReadOnly(!enable);
    endTimeEdit->setReadOnly(!enable);
    monCheck->setEnabled(enable);
    tueCheck->setEnabled(enable);
    wedCheck->setEnabled(enable);
    thuCheck->setEnabled(enable);
    friCheck->setEnabled(enable);
}

void TimetableWindow::storeInput(Subject& subject) //현재입력되어있는값저장
{
    subject.setName(nameEdit->text());
    subject.setLocation(locationEdit->text());
    subject.setStartTime(startTimeEdit->time());
    subject.setEndTime(endTimeEdit->time());
    subject.setMon(monCheck->checkState());
    subject.setTue(tueCheck->checkState());
    subject.setWed(wedCheck->checkState());
    subject.setThu(thuCheck->checkState());
    subject.setFri(friCheck->checkState());
}

void TimetableWindow::clearInput() //모든입력칸값초기화
{
    nameEdit->clear();
    locationEdit->clear();
    startTimeEdit->setTime(QTime(12,00));
    endTimeEdit->setTime(QTime(12,00));
    monCheck->setCheckState(Qt::Unchecked);
    tueCheck->setCheckState(Qt::Unchecked);
    wedCheck->setCheckState(Qt::Unchecked);
    thuCheck->setCheckState(Qt::Unchecked);
    friCheck->setCheckState(Qt::Unchecked);
}

void TimetableWindow::restoreInput(const Subject& subject) //subject값들을입력칸에삽입
{
    nameEdit->setText(subject.getName());
    locationEdit->setText(subject.getLocation());
    startTimeEdit->setTime(subject.getStartTime());
    endTimeEdit->setTime(subject.getEndTime());
    monCheck->setChecked(subject.getMon());
    tueCheck->setChecked(subject.getTue());
    wedCheck->setChecked(subject.getWed());
    thuCheck->setChecked(subject.getThu());
    friCheck->setChecked(subject.getFri());
}

void TimetableWindow::updateInterface(Mode mode) //모드에 따라 입력칸 활성화/비활성화
{
    currentMode = mode;

    switch(currentMode)
    {
        case AddingMode:
        case EditingMode:

            setEnable(true);
            nameEdit->setFocus(Qt::OtherFocusReason);

            addButton->setEnabled(false);
            editButton->setEnabled(false);
            removeButton->setEnabled(false);
            nextButton->setEnabled(false);
            previousButton->setEnabled(false);
            submitButton->setEnabled(true);
            cancelButton->setEnabled(true);
            break;

        case NavigationMode:

            if(subjects.isEmpty())
            {
                clearInput();
            }

            setEnable(false);

            addButton->setEnabled(true);
            int number = subjects.size();
            editButton->setEnabled(number >= 1);
            removeButton->setEnabled(number >= 1);
            nextButton->setEnabled(number > 1);
            previousButton->setEnabled(number > 1);
            submitButton->setEnabled(false);
            cancelButton->setEnabled(false);
            break;
    }
}

int TimetableWindow::findSubjectIndex(const QString& name) const //name이라는 이름의 과목의 index를 리턴
{
    int index = -1; //못찾으면 -1
    for(int i = 0; i < subjects.size(); i++)
    {
        if(subjects[i].getName() == name)
        {
            index = i;
            break;
        }
    }
    return index;
}
