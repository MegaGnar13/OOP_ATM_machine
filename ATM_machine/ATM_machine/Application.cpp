#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <windows.h>
using namespace std;

class Account;
class ATM;
class Bank;

class Bank {
private:

public:
    string Bankname;

    vector<Account*> pAcclist;                   // Bank���� Account ��ü�� �����ͷ� �޴´�.
    vector<ATM*> pATMlist;                       // ������ 1���������� ���߿� �����̸� -> ���� �� �̾����� 2���� ���ͷ� ������.

    vector<int> pcardnum;                        // ī��ѹ�

    Bank() {
        Bankname = "Bank";
        vector<Account*> pAcclist();
        vector<ATM*> pATMlist();
    }

    vector<Account*> get_Account() {             // ���� ������ ����Ʈ ��ȯ
        return pAcclist;
    }

    vector<ATM*> get_ATM() {             // ATM ������ ����Ʈ ��ȯ
        return pATMlist;
    }

    int addAcclist(Account* newAcc) {
        pAcclist.push_back(newAcc);
        return 0;
    }

    int addATMlist(ATM* newATM) {
        pATMlist.push_back(newATM);
        return 0;
    }

    int find_card(int cardnum) {
        auto it = find(pcardnum.begin(), pcardnum.end(), cardnum);
        if (it == pcardnum.end())
            return -1;
        else
            return it - pcardnum.begin();
    }
};

class Daegu_Bank : public Bank {
private:
public:
    Daegu_Bank() {
        Bankname = "DaeguBank";
        vector<Account*> pAcclist();
        vector<ATM*> pATMlist();
    }
};

class Samsung_Bank : public Bank {
private:
public:
    Samsung_Bank() {
        Bankname = "SamsungBank";
        vector<Account*> pAcclist();
        vector<ATM*> pATMlist();
    }
};

class Kakao_Bank : public Bank {
private:
public:
    Kakao_Bank() {
        Bankname = "KakaoBank";
        vector<Account*> pAcclist();
        vector<ATM*> pATMlist();
    }
};

class Account {
private:
    int CardNum;
    int AccNum;
    string Username;
    int AccMoney;
    int Password;
public:
    int get_Cardnum() {
        return CardNum;
    }
    string get_Username() {
        return Username;
    }
    Account();
    Account(int pa_CardNum, int pa_AccNum, string pa_Username, int pa_AccMoney, int pa_Password);
    ~Account();
    void change_Money(int money) {
        AccMoney += money;
        return;
    }

    int HowMoney() { return AccMoney; }
    int getPassword() { return Password; }
};

Account::Account() :CardNum(0), AccNum(0), AccMoney(0), Username("None"), Password(0) {}// ��� ����� ����Ʈ ������ ����

Account::Account(int pa_CardNum, int pa_AccNum, string pa_Username, int pa_AccMoney, int pa_Password) {
    CardNum = pa_CardNum;
    AccNum = pa_AccNum;
    Username = pa_Username;
    AccMoney = pa_AccMoney;
    Password = pa_Password;
}

Account::~Account() {}// �����Ҵ�� �� ������ �ϴ��� �������


class ATM {
private:
    int ATMnum;
    string ATMBank;
    string ATMBankname;
    int ATMmoney; // �ʱⰪ�� õ�������� ����
    bool Single;
    int num_of_deposit_cash;
    int num_of_deposit_check;

    string History;
    int DepoFee;  // 1000��
    int WithdFee; // 1500��
    int SendFee;  // 500��  ���� ���� ����
    Bank* p_AccountNum;
    Bank* p_UserName;
public:
    int get_ATM_num_of_cash() {
        return num_of_deposit_cash;
    }
    int get_ATM_num_of_check() {
        return num_of_deposit_check;
    }
    int get_ATMmoney() {                               // ATMmoney ��ȯ �Լ�
        return ATMmoney;
    }

    void change_ATMmoney(int money) {                      // ATMmoney �� ���ϴ� �Լ�
        ATMmoney += money;
        return;
    }
    string get_ATMBank() {                             // ATMBank ��ȯ �Լ�
        return ATMBank;
    }
    string get_ATMBankname() {
        return ATMBankname;
    }
    bool get_ATMSingle() {
        return Single;
    }
    void add_history(string add_his) {
        History += add_his;
    }
    string get_history() {
        return History;
    }
    int Howmuchfee(string pa_ATMBankname, string pa_current_bank_str, string pa_transaction);    // �Լ� �����ε�
    int Howmuchfee(string pa_ATMBankname, string pa_current_bank_str, string pa_current_tbank_str, string pa_transaction);

    //Deposit(��)->ATM money ����
    ATM(int pa_ATMnum, string pa_ATMBank, string pa_ATMBankname, bool pa_SinorMul, Bank* pa_p_AccountNum, Bank* pa_p_UserName);
    ATM();
    ATM(string pa_ATMBank, string pa_ATMBankname, bool pa_SinorMul) {
        ATMBank = pa_ATMBank;
        ATMBankname = pa_ATMBankname;
        ATMmoney = 10000;
        Single = pa_SinorMul;
        num_of_deposit_cash = 25;
        num_of_deposit_check = 10;
    }
    ~ATM() {}
};

ATM::ATM() : ATMnum(0),ATMBank("None"), ATMmoney(10000000), Single(true), History(nullptr), DepoFee(1000), WithdFee(1500), SendFee(500), p_AccountNum(nullptr), p_UserName(nullptr), num_of_deposit_cash(25), num_of_deposit_check(10) {}// ��� ����� ����Ʈ ������ ����

ATM::ATM(int pa_ATMnum, string pa_ATMBank, string pa_ATMBankname, bool pa_SinorMul, Bank* pa_p_AccountNum, Bank* pa_p_UserName) {
    ATMnum = pa_ATMnum;
    ATMBank = pa_ATMBank;
    ATMmoney = 10000000;
    Single = pa_SinorMul;
    ATMBankname = pa_ATMBankname;
    History = "";
    DepoFee = 1000;
    WithdFee = 1500;
    SendFee = 500;
    // p_AccountNum �� DaeguBank�� �������Ѿ� �ϹǷ� �ϴ��� ����
    // p_UserName �� ���������� ����

}

int ATM::Howmuchfee(string pa_ATMBankname, string pa_current_bank_str, string pa_transaction) {
    if (pa_transaction == "Depos") {
        if (pa_ATMBankname == pa_current_bank_str)
            return 0;
        else
            return 500;
    }
    else if (pa_transaction == "Withd") {
        if (pa_ATMBankname == pa_current_bank_str)
            return 500;
        else
            return 1000;
    }
}

int ATM::Howmuchfee(string pa_ATMBankname, string pa_current_bank_str, string pa_current_tbank_str, string pa_transaction) {
    if (pa_ATMBankname == pa_current_bank_str) {
        if (pa_current_bank_str == pa_current_tbank_str)
            return 1500;
        else
            return 2000;
    }
    if (pa_ATMBankname != pa_current_bank_str) {
        if (pa_current_tbank_str == pa_ATMBankname)
            return 2000;
        else
            return 2500;
    }
}


int main() {

    // Bank �ʱ�ȭ 
    Bank Bank;         // Bank Ŭ������ �ϴ��� ATM ���� ��Ʋ�� ��� �д�
    Daegu_Bank DaeguBank;
    Samsung_Bank SamsungBank;
    Kakao_Bank KakaoBank;

    // ATM �ʱ�ȭ
    ATM DaeguATM("Daegu ATM", "DaeguBank", false);
    ATM DaeguATM_sin("Daegu ATM (DaeguBank only)", "DaeguBank", true);
    ATM SamsungATM("Samsung ATM", "SamsungBank", false);
    ATM SamsungATM_sin("Samsung ATM (SamsungBank only)", "SamsungBank", true);
    ATM KakaoATM("Kakao ATM", "KakaoBank", false);
    ATM KakaoATM_sin("Kakao ATM (KakaoBank only)", "KakaoBank", true);
    ATM atmarr[] = { DaeguATM, DaeguATM_sin, SamsungATM, SamsungATM_sin, KakaoATM, KakaoATM_sin };
    int atmarr_len = sizeof atmarr / sizeof atmarr[0];

    //Bank�� ATM ����

    Bank.addATMlist(&DaeguATM);     // ATM ��ü�� �������ڸ��� �ڵ����� pATMlist�� ���� ���� ���� ������?
    Bank.addATMlist(&DaeguATM_sin);
    Bank.addATMlist(&SamsungATM);
    Bank.addATMlist(&SamsungATM_sin);
    Bank.addATMlist(&KakaoATM);
    Bank.addATMlist(&KakaoATM_sin);

    //Account �ʱ�ȭ
    Account Hong_gil_dong_01(1101, 1111, "Hong gildong", 10000, 1234); //ī���ȣ, ���¹�ȣ, �̸�, �׼�, ��й�ȣ
    Account Kim_chul_su_01(3301, 2222, "Kim chulsu", 10000, 1234);
    Account Park_min_su_01(1111, 3333, "Park minsu", 10000, 1234);
    Account Kim_yu_ri_01(3311, 4444, "Kim yuri", 10000, 1234);
    Account Park_bo_gyung_01(1121, 5555, "Park bogyung", 10000, 1234);
    Account Hong_gil_dong_02(3321, 6666, "Hong gildong", 10000, 1234);
    Account* accarr[] = { &Hong_gil_dong_01, &Kim_chul_su_01, &Park_min_su_01, &Kim_yu_ri_01, &Park_bo_gyung_01, &Hong_gil_dong_02 };
    // ���⼭, �迭�� ������ �迭�� �ƴ� �׳� ��ü�� �迭�� �ϸ� ��� ������Ʈ�� �迭�� "����" �ȴ�!!
    //   -> �� address �� �ٲ�ٴ� ���� �׻� �������!!
    int accarr_len = sizeof accarr / sizeof accarr[0];      // �ð��� ���� main �Լ����� account�� �迭�� ���� ������ �ʿ䰡 ���� ������

    //Account�� cardnum�� �� ���࿡ ����     ----------------> ���߿� �������� ���� �� �������� ������ �ؾ���
    for (int i = 0; i < accarr_len; i++) {
        if (accarr[i]->get_Cardnum() % 100 == 1) {    // Account ��ü�� Cardnum�� 100���� ���� �������� 1�̸� DaeguBank��
            DaeguBank.pcardnum.push_back(accarr[i]->get_Cardnum());
        }
        else if (accarr[i]->get_Cardnum() % 100 == 11) {
            SamsungBank.pcardnum.push_back(accarr[i]->get_Cardnum());
        }
        else if (accarr[i]->get_Cardnum() % 100 == 21) {
            KakaoBank.pcardnum.push_back(accarr[i]->get_Cardnum());
        }
        else {
            cout << "What is this card?" << endl;
        }
    }

    //�� Bank�� Account ����
    for (int i = 0; i < accarr_len; i++)                  // Account ��ü�� �������ڸ��� �ڵ����� pAcclist�� ���� ���� ���� ������?
        if (accarr[i]->get_Cardnum() % 100 == 1) {         // Account ��ü�� Cardnum�� 100���� ���� �������� 1�̸� DaeguBank��
            DaeguBank.addAcclist(accarr[i]);
        }
        else if (accarr[i]->get_Cardnum() % 100 == 11) {   // '''''' �������� 11 �̸� SamsungBank��
            SamsungBank.addAcclist(accarr[i]);
        }
        else if (accarr[i]->get_Cardnum() % 100 == 21) {   // '''''' �������� 21 �̸� KakaoBank�� ����.
            KakaoBank.addAcclist(accarr[i]);
        }

    // ���� ù ȭ��
    int ATM_cnt;
    while (true) {
        Sleep(2000);
        system("cls");//�ܼ� ȭ�� �ʱ�ȭ
        cout << "Please press your ATM number(ex. 1)" << endl;
        cout << endl;
        cout << "0: Quit session" << endl;
        cout << endl;
        for (int i = 0; i < atmarr_len; i++) {
            cout << i + 1 << ". " << (atmarr + i)->get_ATMBank() << " " << endl;
        }
        cout << endl;
        cout << "7: Admin mode " << endl;
        cout << endl;
        
        try {
            cin >> ATM_cnt;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                throw exception("Value error!");
            }
            if (ATM_cnt < 0 || ATM_cnt>7 )
                throw exception("Out of range!");
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }

        if (ATM_cnt == 0) {
            break;
        }

        else if (ATM_cnt == 7) {
            cout << "Admin menu" << endl;
        }

        else {

            ATM* start = Bank.get_ATM()[ATM_cnt - 1];
            cout << endl;
            cout << "Start Banking : " << start->get_ATMBank() << endl;

            cout << endl;
            // ���⼭���� ATM start�� ���ؼ� ���� 

            //cout << "Please insert your card(Enter your card number)" << endl;
            int card_num;
            //cin >> card_num;
            cout << endl;
            int card_index = -1;
            int password;
            auto current_bank = &Bank;          // �ϴ� Bank* Ÿ������ �����ϰ� �ؿ��� �ٿ�ĳ������ �Ѵ�
            string current_bank_str = "";
            // GUI�� class�� �Ұ��� �׳� main�� ������ --> �Ѵ� ����� ���� �� ������ ���߿� ������ ���� ���
            while (true) {
                Sleep(3000);
                system("cls");//�ܼ� ȭ�� �ʱ�ȭ
                cout << "��-----------------------------------------------------��" << endl;
                cout << "��                      " << start->get_ATMBank() << endl;
                cout << "��-----------------------------------------------------��" << endl;
                cout << "�� What do you want to do ? Please press number(ex. 1)" << endl;
                cout << "�� 0. Stop using (Go back ATM_list display)" << endl;
                cout << "�� 1. Cancel" << endl;
                cout << "�� 2. Card insert" << endl;
                cout << "�� 3. Receipt Print" << endl;
                cout << "�� 4. Deposit" << endl;
                cout << "�� 5. Withdrawal" << endl;
                cout << "�� 6. Transfer" << endl;
                cout << "��-----------------------------------------------------��" << endl;
                cout << "��   ��------------------��        ����" << endl;
                cout << "��";
                if (card_index == -1)  cout << "   ��    input card    ��        ����" << endl;
                else cout << "   �� =================��        ����" << endl;
                cout << "��   ��------------------��        ����" << endl;
                cout << "��-----------------------------------------------------��" << endl;

                int press_button;
                try {
                    cin >> press_button;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(100, '\n');
                        throw exception("Value error!");
                    }
                    if (press_button < 0 || press_button>6)
                        throw exception("Out of range!");
                    if (card_index == -1 && press_button > 2)
                        throw exception("No card input");
                }
                catch (exception& e) {
                    cout << e.what() << endl;
                    continue;
                }

                cout << endl;

                if (press_button == 0) {
                    cout << "Thank you for using ATM" << endl;
                    break;
                }
                else if (press_button == 1) {
                    card_index= -1;
                    cout << "Please get a card" << endl;
                    continue;
                }
                else if (press_button == 2) {                              // ī�� ���Է�
                    try {
                        if (card_index == -1) {
                            cout << "Please insert your card(Enter your card number)" << endl;
                            cin >> card_num;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            if (card_num % 100 == 1) {                        // card valid �˻�
                                if (DaeguBank.find_card(card_num) == -1)
                                    throw exception("This card is not valid");
                                cout << "Card is valid" << endl;
                                card_index = DaeguBank.find_card(card_num);
                                current_bank = &DaeguBank;
                                current_bank_str = "DaeguBank";
                            }
                            else if (card_num % 100 == 11) {
                                if (SamsungBank.find_card(card_num) == -1)
                                    throw exception("This card is not valid");
                                cout << "Card is valid" << endl;
                                card_index = SamsungBank.find_card(card_num);
                                current_bank = &SamsungBank;
                                current_bank_str = "SamsungBank";
                            }
                            else if (card_num % 100 == 21) {
                                if (KakaoBank.find_card(card_num) == -1)
                                    throw exception("This card is not valid");
                                cout << "Card is valid" << endl;
                                card_index = KakaoBank.find_card(card_num);
                                current_bank = &KakaoBank;
                                current_bank_str = "KakaoBank";
                            }
                            else
                                throw exception("This card is not valid");

                            if (start->get_ATMSingle() == true) {        // ī�� valid �˻� ���� ATM �̱�/��Ƽ üũ -> Ż�� �� throw -> continue
                                if (start->get_ATMBankname() != current_bank_str) {
                                    card_index = -1;
                                    throw exception("This card is not supported by this ATM machine");
                                }
                                else                                     // �����ϴ� ��쿡�� ���� ���
                                    cout << "This card is useable on this ATM machine" << endl;
                            }
                            else
                                cout << "This card is useable on this ATM machine" << endl; // �����ϴ� ��쿡�� ���� ���
                        }

                        else {
                            cout << "A card is already inserted." << endl;
                            cout << "If you want to work with another card, press button '1'." << endl;
                        }
                        
                    }
                    catch (exception& e) {
                        cout << e.what() << endl;
                        continue;
                    }
                }


                else if (press_button == 3) {
                    cout << "ATM History:" << endl;
                    cout << start->get_history() << endl;
                    /*
                    if (card_num % 100 == 1)
                        cout << DaeguATM.get_history() << endl;
                    else if (card_num % 100 == 11)
                        cout << SamsungATM.get_history() << endl;
                    else if (card_num % 100 == 21)
                        cout << KakaoATM.get_history() << endl;
                        */
                }
                else if (press_button == 4) {
                    //���⼭ Deposit ����
                    Account* Acc_deposit = current_bank->get_Account()[card_index];

                    int One_thousand_won=0;
                    int Five_thousand_won=0;
                    int Ten_tousand_won=0;
                    int Fifty_thousand_won=0;
                    int check=0;
                    

                    
                    
                    string ATMBankname1 = start->get_ATMBankname();
                    int deposit_fee = start->Howmuchfee(ATMBankname1, current_bank_str, "Depos");
                    while (true) {
                        try {
                            cout << "Enter the Enter the number of one_thousand won to deposit: ";
                            cin >> One_thousand_won;
                            if (cin.fail() || One_thousand_won <0) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            cout << "Enter the Enter the number of five_thousand won to deposit: ";
                            cin >> Five_thousand_won;
                            if (cin.fail() || Five_thousand_won <0) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            cout << "Enter the Enter the number of ten_thousand won to deposit: ";
                            cin >> Ten_tousand_won;
                            if (cin.fail() || Ten_tousand_won <0) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            cout << "Enter the Enter the number of fifty_thousand won to deposit: ";
                            cin >> Fifty_thousand_won;
                            if (cin.fail() || Fifty_thousand_won <0) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            cout << "Enter the Enter the number of check to deposit: " ;
                            cin >> check;
                            if (cin.fail() || check <0) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            
                            
                            int deposit_money = 1000 * One_thousand_won + 5000 * Five_thousand_won + 10000 * Ten_tousand_won + 50000 * Fifty_thousand_won;
                           
                            if (deposit_money + 100000*check < deposit_fee)
                                throw exception("Deposited money is smaller than the fee.");      // �Ա� �ݾ��� �����Ẹ�� ���� �� �ٽ� �Ա�

                            int atm_num_of_cash = One_thousand_won + Five_thousand_won + Ten_tousand_won + Fifty_thousand_won;
                            if (atm_num_of_cash > start->get_ATM_num_of_cash() || check > start->get_ATM_num_of_check()) {
                                throw exception("You have exceeded the amount of money(cash or check) you can deposit.");
                            }
                            break;
                        }
                        catch (exception& e) {
                            cout << e.what() << endl;
                            continue;
                        }
                    }
                    int i;
                    for (i = 0; i < 3; i++) {
                        try {
                            cout << "Enter your password" << endl;
                            cin >> password;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Wrong Password");
                            }
                            if (password != Acc_deposit->getPassword())
                                throw password;
                            break;
                        }
                        catch (exception& e) {
                            cout << e.what() << endl;
                            cout << "Password error : " << i + 1 << "times" << endl;
                            continue;
                        }
                        catch (int t) {
                            cout << "Password error : " << i + 1 << "times" << endl;
                        }

                    }
                    if (i == 3) {
                        cout << "too many error" << endl;
                        continue;
                    }
                    // Howmuchfee(string pa_ATMBankname, string pa_current_bank_str, string pa_transaction)

                   
                    int deposit_money = 1000 * One_thousand_won + 5000 * Five_thousand_won + 10000 * Ten_tousand_won + 50000 * Fifty_thousand_won;
                    start->change_ATMmoney(deposit_money);
                    Acc_deposit->change_Money(deposit_money - deposit_fee + 100000*check);
                    start->add_history(Acc_deposit->get_Username() + " deposit $" + to_string(deposit_money) + "\n");

                    cout << "Deposit fee is : " << deposit_fee << endl;
                    cout << Acc_deposit->get_Username() << "'s money : " << Acc_deposit->HowMoney() << endl;
                    cout << "ATM money : " << DaeguATM.get_ATMmoney() << endl;

                    // ���� ����� �ڵ�� ���߿� ������

                    cout << "Hong_gil_dong_01 : " << Hong_gil_dong_01.HowMoney() << endl;
                    cout << "Kim_chul_su_01 : " << Kim_chul_su_01.HowMoney() << endl;
                    cout << "Park_min_su_01 : " << Park_min_su_01.HowMoney() << endl;
                    cout << "Kim_yu_ri_01 : " << Kim_yu_ri_01.HowMoney() << endl;
                    cout << "Park_bo_gyung_01 : " << Park_bo_gyung_01.HowMoney() << endl;
                    cout << "Hong_gil_dong_02 : " << Hong_gil_dong_02.HowMoney() << endl;

                    cout << "DaeguATM : " << DaeguATM.get_ATMmoney() << endl;
                    cout << "DaeguATM (DaeguBank only) : " << DaeguATM_sin.get_ATMmoney() << endl;
                    cout << "SamsungATM : " << SamsungATM.get_ATMmoney() << endl;
                    cout << "SamsungATM (SamsungBank only) : " << SamsungATM_sin.get_ATMmoney() << endl;
                    cout << "KakaoATM : " << KakaoATM.get_ATMmoney() << endl;
                    cout << "KakaoATM (KakaoBank only) : " << KakaoATM_sin.get_ATMmoney() << endl;

                    cout << endl;
                }
                else if (press_button == 5) {
                    //withdrawal 
                    int withdrawal_money;
                    Account* Acc_withdrawal = current_bank->get_Account()[card_index];
                    string ATMBankname1 = start->get_ATMBankname();
                    int withdrawl_fee = start->Howmuchfee(ATMBankname1, current_bank_str, "Withd");
                    while (true) {
                        try {
                            cout << "Enter the money you want to withdrawal" << endl;
                            cin >> withdrawal_money;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            if (withdrawal_money < 0)
                                throw exception("Out of range!");
                            if (withdrawal_money > Acc_withdrawal->HowMoney())
                                throw exception("There is no enough money");
                            break;
                        }
                        catch (exception& e) {
                            cout << e.what() << endl;
                            continue;
                        }
                    }
                    int i;
                    for (i = 0; i < 5; i++) {
                        try {
                            cout << "Enter your password" << endl;
                            cin >> password;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            if (password != Acc_withdrawal->getPassword())
                                throw password;
                            break;
                        }
                        catch (exception& e) {
                            cout << e.what() << endl;
                            continue;
                        }
                        catch (int t) {
                            cout << "Password error : " << i + 1 << "times" << endl;
                        }

                    }
                    if (i == 5) {
                        cout << "too many error" << endl;
                        continue;
                    }
                    start->change_ATMmoney(-withdrawal_money);
                    Acc_withdrawal->change_Money(-withdrawal_money - withdrawl_fee);
                    start->add_history(Acc_withdrawal->get_Username() + " withdrawal $" + to_string(withdrawal_money) + "\n");

                    cout << "Withdrawl fee is : " << withdrawl_fee << endl;
                    cout << Acc_withdrawal->get_Username() << "'s money : " << Acc_withdrawal->HowMoney() << endl;
                    cout << "ATM money : " << DaeguATM.get_ATMmoney() << endl;

                    cout << "Hong_gil_dong_01 : " << Hong_gil_dong_01.HowMoney() << endl;
                    cout << "Kim_chul_su_01 : " << Kim_chul_su_01.HowMoney() << endl;
                    cout << "Park_min_su_01 : " << Park_min_su_01.HowMoney() << endl;
                    cout << "Kim_yu_ri_01 : " << Kim_yu_ri_01.HowMoney() << endl;
                    cout << "Park_bo_gyung_01 : " << Park_bo_gyung_01.HowMoney() << endl;
                    cout << "Hong_gil_dong_02 : " << Hong_gil_dong_02.HowMoney() << endl;

                    cout << "DaeguATM : " << DaeguATM.get_ATMmoney() << endl;
                    cout << "DaeguATM (DaeguBank only) : " << DaeguATM_sin.get_ATMmoney() << endl;
                    cout << "SamsungATM : " << SamsungATM.get_ATMmoney() << endl;
                    cout << "SamsungATM (SamsungBank only) : " << SamsungATM_sin.get_ATMmoney() << endl;
                    cout << "KakaoATM : " << KakaoATM.get_ATMmoney() << endl;
                    cout << "KakaoATM (KakaoBank only) : " << KakaoATM_sin.get_ATMmoney() << endl;

                    cout << endl;
                }
                else if (press_button == 6) {
                    //���⼭ Transfer ����
                    Account* Acc_send = current_bank->get_Account()[card_index];
                    int transfer_money;
                    string ATMBankname1 = start->get_ATMBankname();
                    try {
                        cout << "Enter the money you want to transfer" << endl;
                        cin >> transfer_money;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(100, '\n');
                            throw exception("Value error!");
                        }
                        if (transfer_money < 0)
                            throw exception("Out of range!");
                        if (transfer_money > Acc_send->HowMoney())
                            throw exception("There is no enough money");
                    }
                    catch (exception& e) {
                        cout << e.what() << endl;
                        continue;
                    }
                    int i;
                    for (i = 0; i < 5; i++) {
                        try {
                            cout << "Enter your password" << endl;
                            cin >> password;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            if (password != Acc_send->getPassword())
                                throw password;
                            break;
                        }
                        catch (exception& e) {
                            cout << e.what() << endl;
                            continue;
                        }
                        catch (int t) {
                            cout << "Password error : " << i + 1 << "times" << endl;
                        }

                    }
                    if (i == 5) {
                        cout << "too many error" << endl;
                        continue;
                    }
                    int transfer_card;
                    auto current_tbank = &Bank;
                    string current_tbank_str = "";
                    while (true) {
                        try {
                            cout << "Please enter the card number of the recipient" << endl;
                            cin >> transfer_card;;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            if (card_num == transfer_card)
                                throw exception("This is same card");
                            if (transfer_card % 100 == 1) {                        // card valid �˻�
                                if (DaeguBank.find_card(transfer_card) == -1)
                                    throw exception("This card is not valid");
                                cout << "Card is valid" << endl;
                                current_tbank = &DaeguBank;
                                current_tbank_str = "DaeguBank";
                                break;
                            }
                            else if (transfer_card % 100 == 11) {
                                if (SamsungBank.find_card(transfer_card) == -1)
                                    throw exception("This card is not valid");
                                cout << "Card is valid" << endl;
                                current_tbank = &SamsungBank;
                                current_tbank_str = "SamsungBank";
                                break;
                            }
                            else if (transfer_card % 100 == 21) {
                                if (KakaoBank.find_card(transfer_card) == -1)
                                    throw exception("This card is not valid");
                                cout << "Card is valid" << endl;
                                current_tbank = &KakaoBank;
                                current_tbank_str = "KakaoBank";
                                break;
                            }
                            else
                                throw exception("This card is not valid");
                        }
                        catch (exception& e) {
                            cout << e.what() << endl;
                            continue;
                        }

                    }

                    int transfer_fee = start->Howmuchfee(ATMBankname1, current_bank_str, current_tbank_str, "Trans");

                    Account* Acc_get = current_tbank->get_Account()[current_tbank->find_card(transfer_card)];
                    Acc_send->change_Money(-transfer_money - transfer_fee);
                    Acc_get->change_Money(transfer_money);
                    start->add_history(Acc_send->get_Username() + " transfer $" + to_string(transfer_money) + " to " + Acc_get->get_Username() + "\n");

                    cout << "Transfer fee is : " << transfer_fee << endl;
                    cout << Acc_send->get_Username() << "'s money : " << Acc_send->HowMoney() << endl;
                    cout << Acc_get->get_Username() << "'s money : " << Acc_get->HowMoney() << endl;

                    cout << "Hong_gil_dong_01 : " << Hong_gil_dong_01.HowMoney() << endl;
                    cout << "Kim_chul_su_01 : " << Kim_chul_su_01.HowMoney() << endl;
                    cout << "Park_min_su_01 : " << Park_min_su_01.HowMoney() << endl;
                    cout << "Kim_yu_ri_01 : " << Kim_yu_ri_01.HowMoney() << endl;
                    cout << "Park_bo_gyung_01 : " << Park_bo_gyung_01.HowMoney() << endl;
                    cout << "Hong_gil_dong_02 : " << Hong_gil_dong_02.HowMoney() << endl;

                    cout << endl;
                }
            }



        }
    }

    
    return 0;
}