#include "mainwindow.h"
#include "ui_mainwindow.h"
void major_init();//麻将山初始化
void red_5_check();//查看赤宝牌张数是否为负数
void table_init();//表格初始化
void result_fun();//计算合理出牌
void mosha_evaluate();//手牌评估函数
int major[37];//麻将山
int major_player[4][37];//四家打出牌张数
int major_mosha[4][37];//四家副露
int card;//当前操作的牌张
int isme=0;//判断是否是自己操作
int v_card[10000000];
QString tiao,tong,wan,zi;
typedef  struct
{
    int shunzi=5;
    int pengzi=5;
    int quetou=3;
    int kanzhang=2;
    int qianzhang=2;

}card_score;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    major_init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::red_5_check()
{
    if(major[4]<0)
    {
        major[5]=major[5]+major[4];
        major[4]=0;
    }
    else if(major[5]<0)
    {
        major[4]=0;
        major[5]=0;
    }
    QString displaybuffB = QString::number(major[4],10);
    ui->tableWidget->item(16,4)->setText(displaybuffB);
    displaybuffB = QString::number(major[5],10);
    ui->tableWidget->item(16,5)->setText(displaybuffB);
    if(major[14]<0)
    {
        major[15]=major[15]+major[14];
        major[14]=0;
    }
    else if(major[15]<0)
    {
        major[14]=0;
        major[15]=0;
    }
    displaybuffB = QString::number(major[14],10);
    ui->tableWidget->item(17,4)->setText(displaybuffB);
    displaybuffB = QString::number(major[15],10);
    ui->tableWidget->item(17,5)->setText(displaybuffB);
    if(major[24]<0)
    {
        major[25]=major[25]+major[24];
        major[24]=0;
    }
    else if(major[25]<0)
    {
        major[24]=0;
        major[25]=0;
    }
    displaybuffB = QString::number(major[24],10);
    ui->tableWidget->item(18,4)->setText(displaybuffB);
    displaybuffB = QString::number(major[25],10);
    ui->tableWidget->item(18,5)->setText(displaybuffB);
}

void MainWindow::table_init()
{
    int i,j;
    for(i=0;i<20;i++)
    {
        for(j=0;j<10;j++)
        {
            if((i<16)&&((i%4)!=3))
            {
                ui->tableWidget->item(i,j)->setText("0");
            }
            else if((i<16)&&((i%4)==3))
            {
                if(j<7)
                {
                    ui->tableWidget->item(i,j)->setText("0");
                }
            }
            else if(i>=16&&i<19)
            {
                if((j!=4)&&(j!=5))
                {
                    ui->tableWidget->item(i,j)->setText("4");
                }
                else if(j==4)
                {
                    ui->tableWidget->item(i,j)->setText("1");
                }
                else if(j==5)
                {
                    ui->tableWidget->item(i,j)->setText("3");
                }
            }
            else if(i==19)
            {
                if(j<7)
                {
                    ui->tableWidget->item(i,j)->setText("4");
                }
            }
        }
    }

}

void generateRandomNumber_test()//训练函数
{
    QFile f("D:/project/qt/major/major/doc/data1.txt");
    if(!f.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "Open failed." << endl;
        return ;
    }

    QTextStream txtInput(&f);
    QString lineStr[200000];
    int line=0;//行数
    while(!txtInput.atEnd())
    {
        line++;
        lineStr[line] = txtInput.readLine();
    }
    f.close();
}

void mosha_evaluate(QString mosha)
{
    int i,j,mosha_num[9]={0};
    QString num="123456789";
    for(j=0;j<mosha.length();j++)
    {
        for(i=0;i<9;i++)
        {
            if(num[i]==mosha[j])
            {
                mosha_num[i]++;
                break;
            }
        }
    }
}

void result_fun()//计算合理出牌
{
    int i=0;
    QString mosha;
    generateRandomNumber_test();
    if((tiao.length()!=0)&&(tiao.length()!=14))//条
    {
            mosha=tiao+('1'+i);
            mosha_evaluate(mosha);
    }
    if((tong.length()!=0)&&(tong.length()!=14))//筒
    {

    }
    if((wan.length()!=0)&&(wan.length()!=14))//万
    {

    }
    if((zi.length()!=0)&&(zi.length()!=14))//字
    {

    }
}

void major_init()//麻将山初始化
{
    int i,j;
    for(i=0;i<37;i++)//初始化麻将山
    {
        if(i<30&&i%10==4)
        {
            major[i]=1;
        }
        else if(i<30&&i%10==5)
        {
            major[i]=3;
        }
        else
        {
           major[i]=4;
        }
    }
    for(j=0;j<4;j++)
    {
        for(i=0;i<37;i++)
        {
            major_player[j][i]=0;
            major_mosha[j][i]=0;
        }
    }
}

void MainWindow::radio_button_fun()//radio_button信息处理
{
    int who;
    QString displaybuffA;
    QString displaybuffB;
    if(ui->radioButton->isChecked())//判断操作的玩家是谁（东南西北）
    {
        qDebug()<<"东风玩家"<<endl;
        who=0;
    }
    else if(ui->radioButton_2->isChecked())
    {
        qDebug()<<"南风玩家"<<endl;
        who=1;
    }
    else if(ui->radioButton_3->isChecked())
    {
        qDebug()<<"西风玩家"<<endl;
        who=2;
    }
    else if(ui->radioButton_4->isChecked())
    {
        qDebug()<<"北风玩家"<<endl;
        who=3;
    }
    else
    {
        qDebug()<<"请选择操作对象"<<endl;
        return;
    }


    if(ui->radioButton_5->isChecked())//当前的场风是什么
    {
        qDebug()<<"东风场"<<endl;
    }
    else if(ui->radioButton_6->isChecked())
    {
        qDebug()<<"南风场"<<endl;
    }
    else
    {
        qDebug()<<"请选择本局场风"<<endl;
        return;
    }

    if(ui->radioButton_15->isChecked())//判断自风场
    {
        qDebug()<<"自风东风"<<endl;
        isme=0;

    }
    else if(ui->radioButton_16->isChecked())
    {
        qDebug()<<"自风南风"<<endl;
        isme=1;

    }
    else if(ui->radioButton_14->isChecked())
    {
        qDebug()<<"自风西风"<<endl;
        isme=2;

    }
    else if(ui->radioButton_13->isChecked())
    {
        qDebug()<<"自风北风"<<endl;
        isme=3;

    }
    else
    {
        qDebug()<<"请确定自风场"<<endl;
        return;
    }

    if(ui->radioButton_7->isChecked())//判断操作类型
    {
        qDebug()<<"打"<<endl;
        major_player[who][card]++;
        major[card]--;
        displaybuffA = QString::number(major_player[who][card],10);
        displaybuffB = QString::number(major[card],10);
        ui->tableWidget->item(((who*4)+(card/10)),(card%10))->setText(displaybuffA);
        ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
        if(who==0)
        {
            ui->radioButton_2->setChecked(true);
        }
        else if(who==1)
        {
            ui->radioButton_3->setChecked(true);
        }
        else if(who==2)
        {
            ui->radioButton_4->setChecked(true);
        }
        else if(who==3)
        {
            ui->radioButton->setChecked(true);
        }
    }
    else if(ui->radioButton_8->isChecked())
    {
        qDebug()<<"手牌"<<endl;
        tiao=ui->lineEdit->displayText();
        tong=ui->lineEdit_2->displayText();
        wan=ui->lineEdit_3->displayText();
        zi=ui->lineEdit_4->displayText();
        result_fun();
    }
    else if(ui->radioButton_9->isChecked())
    {
        qDebug()<<"碰"<<endl;
        major_mosha[who][card]+=3;
        major[card]-=3;
        displaybuffB = QString::number(major[card],10);
        ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
    }
    else if(ui->radioButton_10->isChecked())
    {
        qDebug()<<"杠"<<endl;
        major_mosha[who][card]+=4;
        major[card]-=4;
        displaybuffB = QString::number(major[card],10);
        ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
    }
    else if(ui->radioButton_11->isChecked())
    {
        qDebug()<<"撤回"<<endl;
        major_player[who][card]--;
        major[card]++;
        displaybuffA = QString::number(major_player[who][card],10);
        displaybuffB = QString::number(major[card],10);
        ui->tableWidget->item(((who*4)+(card/10)),(card%10))->setText(displaybuffA);
        ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
    }
    else if(ui->radioButton_12->isChecked())
    {
        qDebug()<<"新一局"<<endl;
        ui->radioButton->setChecked(true);
        if(isme==0)
        {
            ui->radioButton_13->setChecked(true);
        }
        else if(isme==1)
        {
            ui->radioButton_15->setChecked(true);
        }
        else if(isme==2)
        {
            ui->radioButton_16->setChecked(true);
        }
        else if(isme==3)
        {
            ui->radioButton_14->setChecked(true);
            if(ui->radioButton_5->isChecked())
            {
                ui->radioButton_6->setChecked(true);
            }
            else if(ui->radioButton_6->isChecked())
            {
                ui->radioButton_5->setChecked(true);
            }
        }
        major_init();
        table_init();
    }
    else if(ui->radioButton_17->isChecked())
    {
        qDebug()<<"左吃"<<endl;
        major_mosha[who][card]++;major[card]--;
        displaybuffB = QString::number(major[card],10);
        ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
        if((card%10)==4)
        {
            card+=2;
            major_mosha[who][card]++;major[card]--;
            displaybuffB = QString::number(major[card],10);
            ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
        }
        else
        {
            major_mosha[who][++card]++;major[card]--;
            displaybuffB = QString::number(major[card],10);
            ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
        }
        if((card%10)==4)
        {
            card+=2;
            major_mosha[who][card]++;major[card]--;
            displaybuffB = QString::number(major[card],10);
            ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
        }
        else
        {
            major_mosha[who][++card]++;major[card]--;
            displaybuffB = QString::number(major[card],10);
            ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
        }
    }
    else if(ui->radioButton_18->isChecked())
    {
        qDebug()<<"中吃"<<endl;
        major_mosha[who][card]++;major[card]--;
        displaybuffB = QString::number(major[card],10);
        ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
        if((card%10)==5)
        {
            card-=2;
            major_mosha[who][card]++;major[card]--;
            displaybuffB = QString::number(major[card],10);
            ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
            card+=2;
        }
        else
        {
            major_mosha[who][card--]++;major[card]--;
            displaybuffB = QString::number(major[card],10);
            ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
            card++;
        }
        if((card%10)==4)
        {
            card+=2;
            major_mosha[who][card]++;major[card]--;
            displaybuffB = QString::number(major[card],10);
            ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
        }
        else
        {
            major_mosha[who][++card]++;major[card]--;
            displaybuffB = QString::number(major[card],10);
            ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
        }
    }
    else if(ui->radioButton_19->isChecked())
    {
        qDebug()<<"右吃"<<endl;
        major_mosha[who][card]++;major[card]--;
        displaybuffB = QString::number(major[card],10);
        ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
        if((card%10)==5)
        {
            card-=2;
            major_mosha[who][card]++;major[card]--;
            displaybuffB = QString::number(major[card],10);
            ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
        }
        else
        {
            major_mosha[who][card--]++;major[card]--;
            displaybuffB = QString::number(major[card],10);
            ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
        }
        if((card%10)==5)
        {
            card-=2;
            major_mosha[who][card]++;major[card]--;
            displaybuffB = QString::number(major[card],10);
            ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
        }
        else
        {
            major_mosha[who][card--]++;major[card]--;
            displaybuffB = QString::number(major[card],10);
            ui->tableWidget->item((16+(card/10)),(card%10))->setText(displaybuffB);
        }
    }
    else
    {
        qDebug()<<"请选择需要执行的操作"<<endl;
        return;
    }
    red_5_check();
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"一条"<<endl;
    card=0;
    radio_button_fun();
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"二条"<<endl;
    card=1;
    radio_button_fun();
}

void MainWindow::on_pushButton_3_clicked()
{
    qDebug()<<"三条"<<endl;
    card=2;
    radio_button_fun();
}

void MainWindow::on_pushButton_4_clicked()
{
    qDebug()<<"四条"<<endl;
    card=3;
    radio_button_fun();
}

void MainWindow::on_pushButton_5_clicked()
{
    qDebug()<<"赤五条"<<endl;
    card=4;
    radio_button_fun();
}

void MainWindow::on_pushButton_6_clicked()
{
    qDebug()<<"五条"<<endl;
    card=5;
    radio_button_fun();
}

void MainWindow::on_pushButton_7_clicked()
{
    qDebug()<<"六条"<<endl;
    card=6;
    radio_button_fun();
}


void MainWindow::on_pushButton_8_clicked()
{
    qDebug()<<"七条"<<endl;
    card=7;
    radio_button_fun();
}

void MainWindow::on_pushButton_9_clicked()
{
    qDebug()<<"八条"<<endl;
    card=8;
    radio_button_fun();
}

void MainWindow::on_pushButton_10_clicked()
{
    qDebug()<<"九条"<<endl;
    card=9;
    radio_button_fun();
}

void MainWindow::on_pushButton_11_clicked()
{
    qDebug()<<"一筒"<<endl;
    card=10;
    radio_button_fun();
}

void MainWindow::on_pushButton_13_clicked()
{
    qDebug()<<"二筒"<<endl;
    card=11;
    radio_button_fun();
}

void MainWindow::on_pushButton_16_clicked()
{
    qDebug()<<"三筒"<<endl;
    card=12;
    radio_button_fun();
}

void MainWindow::on_pushButton_17_clicked()
{
    qDebug()<<"四筒"<<endl;
    card=13;
    radio_button_fun();
}

void MainWindow::on_pushButton_18_clicked()
{
    qDebug()<<"赤五筒"<<endl;
    card=14;
    radio_button_fun();
}

void MainWindow::on_pushButton_12_clicked()
{
    qDebug()<<"五筒"<<endl;
    card=15;
    radio_button_fun();
}

void MainWindow::on_pushButton_20_clicked()
{
    qDebug()<<"六筒"<<endl;
    card=16;
    radio_button_fun();
}

void MainWindow::on_pushButton_19_clicked()
{
    qDebug()<<"七筒"<<endl;
    card=17;
    radio_button_fun();
}

void MainWindow::on_pushButton_14_clicked()
{
    qDebug()<<"八筒"<<endl;
    card=18;
    radio_button_fun();
}

void MainWindow::on_pushButton_15_clicked()
{
    qDebug()<<"九筒"<<endl;
    card=19;
    radio_button_fun();
}

void MainWindow::on_pushButton_21_clicked()
{
    qDebug()<<"一万"<<endl;
    card=20;
    radio_button_fun();
}

void MainWindow::on_pushButton_23_clicked()
{
    qDebug()<<"二万"<<endl;
    card=21;
    radio_button_fun();
}

void MainWindow::on_pushButton_26_clicked()
{
    qDebug()<<"三万"<<endl;
    card=22;
    radio_button_fun();
}

void MainWindow::on_pushButton_27_clicked()
{
    qDebug()<<"四万"<<endl;
    card=23;
    radio_button_fun();
}

void MainWindow::on_pushButton_28_clicked()
{
    qDebug()<<"赤五万"<<endl;
    card=24;
    radio_button_fun();
}

void MainWindow::on_pushButton_22_clicked()
{
    qDebug()<<"五万"<<endl;
    card=25;
    radio_button_fun();
}

void MainWindow::on_pushButton_30_clicked()
{
    qDebug()<<"六万"<<endl;
    card=26;
    radio_button_fun();
}

void MainWindow::on_pushButton_29_clicked()
{
    qDebug()<<"七万"<<endl;
    card=27;
    radio_button_fun();
}

void MainWindow::on_pushButton_24_clicked()
{
    qDebug()<<"八万"<<endl;
    card=28;
    radio_button_fun();
}

void MainWindow::on_pushButton_25_clicked()
{
    qDebug()<<"九万"<<endl;
    card=29;
    radio_button_fun();
}

void MainWindow::on_pushButton_33_clicked()
{
    qDebug()<<"东风"<<endl;
    card=30;
    radio_button_fun();
}

void MainWindow::on_pushButton_35_clicked()
{
    qDebug()<<"南风"<<endl;
    card=31;
    radio_button_fun();
}

void MainWindow::on_pushButton_38_clicked()
{
    qDebug()<<"西风"<<endl;
    card=32;
    radio_button_fun();
}

void MainWindow::on_pushButton_36_clicked()
{
    qDebug()<<"北风"<<endl;
    card=33;
    radio_button_fun();
}

void MainWindow::on_pushButton_37_clicked()
{
    qDebug()<<"红中"<<endl;
    card=34;
    radio_button_fun();
}

void MainWindow::on_pushButton_34_clicked()
{
    qDebug()<<"白板"<<endl;
    card=35;
    radio_button_fun();
}

void MainWindow::on_pushButton_32_clicked()
{
    qDebug()<<"发财"<<endl;
    card=36;
    radio_button_fun();
}
