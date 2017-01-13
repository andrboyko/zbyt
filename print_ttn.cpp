#include "print_ttn.h"
#include "ui_print_ttn.h"

print_ttn::print_ttn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::print_ttn)
{
    ui->setupUi(this);
}

print_ttn::~print_ttn()
{
    delete ui;
}

void print_ttn::on_pushButton_clicked()
{
    hide();
    query = new QSqlQuery();
    file=new QFile;
    file->setFileName("C:/Temp/test.html");
    file->open(QIODevice::WriteOnly);

    QTextStream in(file);
    in.setCodec("UTF-8");
    in <<QString("<!DOCTYPE HTML>");
    in <<QString("<HTML>");
    in <<QString("<HEAD>");
    in <<QString("    <TITLE>Податкова накладна</TITLE>");
    in <<QString("    <meta charset='UTF-8'>");
    in <<QString("    <link href=\"css\\podatkova.css\" rel=\"stylesheet\" type=\"text/css\"> </HEAD>");

    in <<QString("<BODY>");
    in <<QString("    <div id=\"page_align\">");
    in <<QString("        <div id=\"header\">");
    in <<QString("            <div id=\"header_right\">");
    in <<QString("                <p> ЗАТВЕРДЖЕНО");
    in <<QString("                    <p>Наказ Державної податкової");
    in <<QString("                        <p>адміністрації України");
    in <<QString("                            <p>21.12.2010 №969 </div>");
    in <<QString("            <div id=\"header_left\">");
    in <<QString("                <table style=\" border-collapse: collapse;   text-align: center; height:120px; width:225px;\" border=1px;>");
    in <<QString("                    <tr>");
    in <<QString("                        <td rowspan=\"4\">Оригінал</td>");
    in <<QString("                        <td>Видається покупцю</td>");
    in <<QString("                        <td colspan=\"2\" ; width=\"26px\"></td>");
    in <<QString("                    </tr>");
    in <<QString("                    <tr>");
    in <<QString("                        <td>Включено до ЕРПН</td>");
    in <<QString("                        <td colspan=\"2\" ; width=\"26px\"></td>");
    in <<QString("                    </tr>");
    in <<QString("                    <tr>");
    in <<QString("                        <td rowspan=\"2\">Залишається у продавця");
    in <<QString("                            <p>(тип причини)</td>");
    in <<QString("                        <td colspan=\"2\" ; width=\"26px\"></td>");
    in <<QString("                    </tr>");
    in <<QString("                    <tr>");
    in <<QString("                        <td></td>");
    in <<QString("                        <td></td>");
    in <<QString("                    </tr>");
    in <<QString("                    <tr>");
    in <<QString("                        <td colspan=\"2\">Копія (залишається у продавця)</td>");
    in <<QString("                        <td colspan=\"2\" ; width=\"26px\"></td>");
    in <<QString("                    </tr>");
    in <<QString("                </table>");
    in <<QString("                <p>(Потрібне виділити 'X') </div>");
    in <<QString("        </div>");
    in <<QString("        <h2 align=center>Податкова накладна</h2>");
    in <<QString("        <div id=\"date_nomer\">");
    in <<QString("<table><tr>");
    in <<QString("<td>Дата виписки податкової накладної</td>");
    in <<QString("<td><table id=\"table_property\" border=\"1\"><tr>");

    query->exec("SELECT DATE_FORMAT((SELECT ttn_date FROM zbyt.ttn WHERE ttn_id="+QString::number(index_table)+") , '%d%m%Y');");
    query->next();
    foreach(QChar c, query->value(0).toString()){
        in <<QString("                            <td>" + QString(c) + "</td>");
    }

    in <<QString("</tr></table></td>");

    in <<QString("<td style=\"padding-left:150px\">Порядковий номер</td>");
    in <<QString("<td> <table id=\"table_property\" border=\"1\"><tr>");

    query->exec("SELECT ttn_id FROM ttn WHERE ttn_id="+QString::number(index_table)+";");
    query->next();
    foreach(QChar c, query->value(0).toString()){
        in <<QString("                            <td>" + QString(c) + "</td>");
    }
    in <<QString("</tr></table></td>");
    in <<QString("<td><span style=\"font-size:16px\">\\</span></td>");
    in <<QString("<td><table border=\"1\" width=\"60px\" height=\"20px\" style=\"border-collapse: collapse; text-align: center;\">");
    in <<QString("<tr><td>1</td><td>&nbsp&nbsp</td><td>&nbsp&nbsp</td></table></td></tr>");
    in <<QString("</table></div>");

    in <<QString("<div id=\"property\">");
    in <<QString("<div id=\"property_saller\">");
    in <<QString("<p align=center><i>ПРОДАВЕЦЬ</i></p>");

    in <<QString("<table><tr><td>Особа (платник податку)-продавець</td>");
    query->exec("SELECT requisites_name FROM our_requisites;");
    query->next();
    in <<QString("<td><p id=\"text_border\">"+query->value(0).toString()+"</p></td></tr>");

    in <<QString("<tr><td>Індивідуальний податковий номер</td><td>");
    in <<QString("<table id=\"table_property\" border=\"1\"><tr>");
    query->exec("SELECT individual_nomer FROM our_requisites;");
    query->next();
    foreach(QChar c, query->value(0).toString()){
        in <<QString("                            <td>" + QString(c) + "</td>");
    }
    in <<QString("</tr></table></td></tr>");

    in <<QString("<tr><td>Місцезнаходження (податкова адреса) продавця</td>");
    in <<QString("<td>               ");
    query->exec("SELECT address FROM our_requisites;");
    query->next();
    in <<QString("<p id=\"text_border\">"+query->value(0).toString()+"</p></td></tr>");

    in <<QString("<tr><td>Номер телефону</td>");
    in <<QString("<td><table id=\"table_property\" border=\"1\"></tr> ");
    query->exec("SELECT tel FROM our_requisites;");
    query->next();
    foreach(QChar c, query->value(0).toString()){
        in <<QString("                            <td>" + QString(c) + "</td>");
    }
    in <<QString("</tr></table></td></tr>");
    in <<QString("<tr><td>Номер свідоцтва про реєстрацію платника податку на додану вартість (продавця)</td>");
    in <<QString("<td><table id=\"table_property\" border=\"1\"><tr>");
    query->exec("SELECT n_reg_svid FROM our_requisites;");
    query->next();
    foreach(QChar c, query->value(0).toString()){
        in <<QString("                            <td>" + QString(c) + "</td>");
    }
    in <<QString("</tr></table></td></tr>");
    in <<QString("</table></div>");


    in <<QString("<div id=\"property_custumers\">");
    in <<QString("<p align=center><i>ПОКУПЕЦЬ</i></p>");
    in <<QString("<table><tr><td>Особа (платник податку)-покупець</td><td>");
    query->exec("SELECT cust_name FROM custumers, ttn WHERE custumers.cust_id=ttn.cust_id AND ttn_id="+QString::number(index_table)+";");
    query->next();
    in <<QString("<p id=\"text_border\">"+query->value(0).toString()+"</p></td></tr>");

    in <<QString("<tr><td>Індивідуальний податковий номер</td><td>");
    in <<QString("<table id=\"table_property\" border=\"1\"><tr>");
    query->exec("SELECT kod_pp FROM custumers, ttn WHERE custumers.cust_id=ttn.cust_id AND ttn_id="+QString::number(index_table)+";");
    query->next();
    if(query->value(0).toString()!=""){
        foreach(QChar c, query->value(0).toString()){
            in <<QString("                            <td>" + QString(c) + "</td>");
        }
    }else{
        for (int i=0; i<=9; i++){
            in <<QString("                            <td>&nbsp&nbsp</td>");
        }
    }
    in <<QString("</tr></table></td></tr>");

    in <<QString("<tr><td>Місцезнаходження (податкова адреса) покупця</td><td>");
    query->exec("SELECT address FROM custumers, ttn WHERE custumers.cust_id=ttn.cust_id AND ttn_id="+QString::number(index_table)+";");
    query->next();
    in <<QString("<p id=\"text_border\">"+query->value(0).toString()+"</p></td></tr>");


    in <<QString("<tr><td>Номер телефону</td><td>");
    in <<QString("<table id=\"table_property\" border=\"1\"></tr>");
    query->exec("SELECT tel FROM custumers, ttn WHERE custumers.cust_id=ttn.cust_id AND ttn_id="+QString::number(index_table)+";");
    query->next();
    if(query->value(0).toString()!=""){
        foreach(QChar c, query->value(0).toString())
        {
            in <<QString("                            <td>" + QString(c) + "</td>");
        }
    }else{
        for (int i=0; i<=9; i++){
            in <<QString("                            <td>&nbsp&nbsp</td>");
        }
    }
    in <<QString("</tr></table></td></tr>");

    in <<QString("<tr><td>Номер свідоцтва про реєстрацію платника податку на додану вартість (покупця)</td><td>");
    in <<QString("<table id=\"table_property\" border=\"1\"><tr>");
    query->exec("SELECT n_reg_svid FROM custumers, ttn WHERE custumers.cust_id=ttn.cust_id AND ttn_id="+QString::number(index_table)+";");
    query->next();
    if(query->value(0).toString()!=""){

        foreach(QChar c, query->value(0).toString())
        {
            in <<QString("                            <td>" + QString(c) + "</td>");
        }
    }else{
        for (int i=0; i<=9; i++){
            in <<QString("                            <td>&nbsp&nbsp</td>");
        }
    }
    in <<QString("</tr></table></td></tr></table>");
    in <<QString("        </div>");
    in <<QString("        </div>");
    in <<QString("        <div id=\"dogovir\">");
    in <<QString("<table><tr><td>Вид цивільного проавового договору</td>");
    in <<QString("<td><span id=\"text_border10\">11111111</span></td>");
    in <<QString("<td>від</td>");
    in <<QString("<td><table border=\"1\" id=\"table_property\">");
    in <<QString("<tr><td>0</td><td>4</td><td>0</td><td>1</td><td>2</td><td>0</td><td>1</td><td>1</td></tr></table></td>");
    in <<QString("<td><span style=\"font-size:14px\">№</span></td>");
    in <<QString("<td><table border=\"1\" id=\"table_property\">");
    in <<QString("<tr><td>&nbsp&nbsp</td><td>&nbsp&nbsp</td><td>&nbsp&nbsp</td><td>&nbsp&nbsp</td><td>&nbsp&nbsp</td><td>&nbsp&nbsp</td><td>&nbsp&nbsp</td>");
    in <<QString("</table></td></tr></table> ");
    in <<QString("        <p> Форма проведених розрахунків <span id=\"text_border10\">Готівковий розрахунок</span>");
    in <<QString("            <p>");
    in <<QString("                <div id=\"table\">");
    in <<QString("                    <table style=\"font-size:12px; border-collapse:collapse; text-align:center;\" ; border=1px;>");
    in <<QString("                        <tr>");
    in <<QString("                            <td rowspan=\"2\">Розділ</td>");
    in <<QString("                            <td rowspan=\"2\" width=\"20\">Дата відвантаження виконання, постачання</td>");
    in <<QString("                            <td rowspan=\"2\">Номенклатура постачання товарів/послуг продавця</td>");
    in <<QString("                            <td rowspan=\"2\">Одиниця виміру товару</td>");
    in <<QString("                            <td rowspan=\"2\">Кількість</td>");
    in <<QString("                            <td rowspan=\"2\" width=\"1\">Ціна постачання одиниці товару/послуги без урахування ПДВ</td>");
    in <<QString("                            <td colspan=\"4\">Обсяги постачання(база оподаткування) без урахування ПДВ що підлягають оподаткуванню за ставками</td>");
    in <<QString("                            <td rowspan=\"2\">Загальна сума коштів що підлягають оплаті</td>");
    in <<QString("                        </tr>");
    in <<QString("                        <tr>");
    in <<QString("                            <td>20%</td>");
    in <<QString("                            <td>0% (постач. на митній території України)</td>");
    in <<QString("                            <td>0% (експорт)</td>");
    in <<QString("                            <td>Звільнення від ПДВ **</td>");
    in <<QString("                        </tr>");
    in <<QString("                        <tr>");
    in <<QString("                            <td>1</td>");
    in <<QString("                            <td>2</td>");
    in <<QString("                            <td>3</td>");
    in <<QString("                            <td>4</td>");
    in <<QString("                            <td>5</td>");
    in <<QString("                            <td>6</td>");
    in <<QString("                            <td>7</td>");
    in <<QString("                            <td>8</td>");
    in <<QString("                            <td>9</td>");
    in <<QString("                            <td>10</td>");
    in <<QString("                            <td>11</td>");
    in <<QString("                        </tr>");
    in <<QString("                        <tr>");

    query->exec("SELECT prod_id FROM zbyt.ttn_items WHERE ttn_id="+QString::number(index_table)+";");
    int i=0;
    while (query->next()) {
        i++;
    }
    in <<QString("                            <td rowspan=\""+QString::number(i)+"\">I</td>");
    in <<QString("                            <td rowspan=\""+QString::number(i)+"\">");
    query->exec("SELECT DATE_FORMAT((SELECT ttn_date FROM zbyt.ttn WHERE ttn_id="+QString::number(index_table)+") , '%d.%m%.%y');");
    query->next();
    in <<QString(""+query->value(0).toString()+"</td>");
    i=0;
    query->exec("SELECT prod_name, units_name, ttn_item_quantity, ttn_item_price  FROM products, ttn_items, units WHERE products.prod_id=ttn_items.prod_id AND units.units_id=products.units_id AND ttn_id="+QString::number(index_table) +";");
    while (query->next()) {
         if (i>0){
             in <<QString("<tr>");
         }
         in <<QString("                            <td>"+query->value(0).toString()+"</td>");
         in <<QString("                            <td>"+query->value(1).toString()+"</td>");
         in <<QString("                            <td>"+query->value(2).toString()+"</td>");
         in <<QString("                            <td>"+query->value(3).toString()+"</td>");
         in <<QString("                            <td>"+QString::number(query->value(2).toDouble()*query->value(3).toDouble())+"</td>");
         in <<QString("                            <td></td>");
         in <<QString("                            <td></td>");
         in <<QString("                            <td></td>");
         in <<QString("                            <td></td>");
         in <<QString("</tr>");
    i++;
    }

    in <<QString("                        <tr>");
    in <<QString("                            <tr>");
    in <<QString("                                <td></td>");
    in <<QString("                                <td colspan=\"2\">Усього по розділу I</td>");
    in <<QString("                                <td>X</td>");
    in <<QString("                                <td>X</td>");
    in <<QString("                                <td>X</td>");

    query->exec("SELECT sum FROM ttn WHERE ttn_id="+QString::number(index_table) +";");
    query->next();

    in <<QString("                                <td>"+query->value(0).toString()+"</td>");
    in <<QString("                                <td></td>");
    in <<QString("                                <td></td>");
    in <<QString("                                <td></td>");
    in <<QString("                                <td>10402.17</td>");
    in <<QString("                            </tr>");
    in <<QString("                            <tr>");
    in <<QString("                                <td>II</td>");
    in <<QString("                                <td colspan=\"2\">Зворотня (заставна) тара</td>");
    in <<QString("                                <td>X</td>");
    in <<QString("                                <td>X</td>");
    in <<QString("                                <td>X</td>");
    in <<QString("                                <td>X</td>");
    in <<QString("                                <td>X</td>");
    in <<QString("                                <td>X</td>");
    in <<QString("                                <td>X</td>");
    in <<QString("                                <td></td>");
    in <<QString("                            </tr>");
    in <<QString("                            <tr>");
    in <<QString("                                <td>III</td>");
    in <<QString("                                <td colspan=\"2\">Податок на додану вартість</td>");
    in <<QString("                                <td>X</td>");
    in <<QString("                                <td>X</td>");
    in <<QString("                                <td>X</td>");
    in <<QString("                                <td>"+QString::number((query->value(0).toDouble()*0.2))+"</td>");
    in <<QString("                                <td></td>");
    in <<QString("                                <td></td>");
    in <<QString("                                <td></td>");
    in <<QString("                                <td>"+QString::number((query->value(0).toDouble()*0.2))+"</td>");
    in <<QString("                            </tr>");
    in <<QString("                            <tr>");
    in <<QString("                                <td>IV</td>");
    in <<QString("                                <td colspan=\"2\">Загальна сума з ПДВ</td>");
    in <<QString("                                <td>X</td>");
    in <<QString("                                <td>X</td>");
    in <<QString("                                <td>X</td>");
    in <<QString("                                <td>"+QString::number((query->value(0).toDouble()*1.2))+"</td>");
    in <<QString("                                <td>X</td>");
    in <<QString("                                <td></td>");
    in <<QString("                                <td></td>");
    in <<QString("                                <td>"+QString::number((query->value(0).toDouble()*1.2))+"</td>");
    in <<QString("                            </tr>");
    in <<QString("                    </table>");
    in <<QString("                </div>");
    in <<QString("                <p>Суми ПДВ нараховані(сплачені у звязку з постачанням товарів/послуг), зазначених у цій накладній, визначені правильно, відповідають сумі податкових зобовя`заннь продавця і включені до реєстру виданих та отриманих податкових накладних</p>");
    in <<QString("<div id=\"podpis\">");
    in <<QString("<table width=\"90%\"><tr>");
    in <<QString("<td style=\"text-align:right\" width=\"25%\" ><b>М.П</b></td>");
    in <<QString("<td style=\"text-align:right\"><span id=\"text_border\">&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbspА.М.Пастир</span>");
    in <<QString("</td></tr> </table>");
    in <<QString("</div> (*)Дата оплати ставиться у разі попередньої оплати постачання, на яку виписується податкова накладна, для операцій з постачання товарів/послуг відповідно до пункту 187.10 статті 187 розділу V Податкового кодексу України. </p>");
    in <<QString("<p> (**)______________________________________________________________________________________________________________________</p>");
    in <<QString("<p>(відповідні пункти (підпункти), статті, підрозділи, розділи Податкового кодексу України, якими передбачено звільнення від оподаткування)</p>");
    in <<QString("</div>");
    in <<QString("</BODY>");
    in <<QString("</HTML>");

    QProcess::execute("cmd /c start firefox.exe \"file:///C:/Temp/test.html\"");

    close();
}

void print_ttn::on_pushButton_2_clicked()
{

}

void print_ttn::on_pushButton_3_clicked()
{

}

void print_ttn::on_pushButton_4_clicked()
{
    close();
}

void print_ttn::receiveData(int i, bool e)
{
    index_table=i;
}




