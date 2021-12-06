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

    vector<Account*> pAcclist;                   // Bank에서 Account 객체를 포인터로 받는다.
    vector<ATM*> pATMlist;                       // 지금은 1차원이지만 나중엔 유저이름 -> 계좌 로 이어지는 2차원 벡터로 만들자.

    vector<int> pcardnum;                        // 카드넘버

    Bank() {
        Bankname = "Bank";
        vector<Account*> pAcclist();
        vector<ATM*> pATMlist();
    }

    vector<Account*> get_Account() {             // 계좌 포인터 리스트 반환
        return pAcclist;
    }

    vector<ATM*> get_ATM() {             // ATM 포인터 리스트 반환
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

Account::Account() :CardNum(0), AccNum(0), AccMoney(0), Username("None"), Password(0) {}// 모든 멤버를 디폴트 값으로 생성

Account::Account(int pa_CardNum, int pa_AccNum, string pa_Username, int pa_AccMoney, int pa_Password) {
    CardNum = pa_CardNum;
    AccNum = pa_AccNum;
    Username = pa_Username;
    AccMoney = pa_AccMoney;
    Password = pa_Password;
}

Account::~Account() {}// 동적할당된 게 없으니 일단은 비워놓음


class ATM {
private:
    int ATMnum;
    string ATMBank;
    string ATMBankname;
    int ATMmoney; // 초기값을 천만원으로 설정
    bool Single;
    int num_of_deposit_cash;
    int num_of_deposit_check;

    string History;
    int DepoFee;  // 1000원
    int WithdFee; // 1500원
    int SendFee;  // 500원  으로 각각 설정
    Bank* p_AccountNum;
    Bank* p_UserName;
public:
    int get_ATM_num_of_cash() {
        return num_of_deposit_cash;
    }
    int get_ATM_num_of_check() {
        return num_of_deposit_check;
    }
    int get_ATMmoney() {                               // ATMmoney 반환 함수
        return ATMmoney;
    }

    void change_ATMmoney(int money) {                      // ATMmoney 돈 더하는 함수
        ATMmoney += money;
        return;
    }
    string get_ATMBank() {                             // ATMBank 반환 함수
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
    int Howmuchfee(string pa_ATMBankname, string pa_current_bank_str, string pa_transaction);    // 함수 오버로딩
    int Howmuchfee(string pa_ATMBankname, string pa_current_bank_str, string pa_current_tbank_str, string pa_transaction);

    //Deposit(돈)->ATM money 증가
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

ATM::ATM() : ATMnum(0), ATMBank("None"), ATMmoney(10000000), Single(true), History(nullptr), DepoFee(1000), WithdFee(1500), SendFee(500), p_AccountNum(nullptr), p_UserName(nullptr), num_of_deposit_cash(25), num_of_deposit_check(10) {}// 모든 멤버를 디폴트 값으로 생성

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
    // p_AccountNum 는 DaeguBank와 연동시켜야 하므로 일단은 보류
    // p_UserName 도 마찬가지로 보류

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
    else if (pa_transaction == "Trans") {
        if (pa_ATMBankname == pa_current_bank_str) {
            return 1500;
        }
        else {
            return 2000;
        }
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

    // Bank 초기화 
    Bank Bank;         // Bank 클래스는 일단은 ATM 구현 셔틀로 계속 둔다
    Daegu_Bank DaeguBank;
    Samsung_Bank SamsungBank;
    Kakao_Bank KakaoBank;

    // ATM 초기화
    ATM DaeguATM("Daegu ATM", "DaeguBank", false);
    ATM DaeguATM_sin("Daegu ATM (DaeguBank only)", "DaeguBank", true);
    ATM SamsungATM("Samsung ATM", "SamsungBank", false);
    ATM SamsungATM_sin("Samsung ATM (SamsungBank only)", "SamsungBank", true);
    ATM KakaoATM("Kakao ATM", "KakaoBank", false);
    ATM KakaoATM_sin("Kakao ATM (KakaoBank only)", "KakaoBank", true);
    ATM atmarr[] = { DaeguATM, DaeguATM_sin, SamsungATM, SamsungATM_sin, KakaoATM, KakaoATM_sin };
    int atmarr_len = sizeof atmarr / sizeof atmarr[0];

    //Bank에 ATM 연결

    Bank.addATMlist(&DaeguATM);     // ATM 객체가 생성되자마자 자동으로 pATMlist에 들어가게 만들 수는 없을까?
    Bank.addATMlist(&DaeguATM_sin);
    Bank.addATMlist(&SamsungATM);
    Bank.addATMlist(&SamsungATM_sin);
    Bank.addATMlist(&KakaoATM);
    Bank.addATMlist(&KakaoATM_sin);

    //Account 초기화
    Account Hong_gil_dong_01(1101, 1111, "Hong gildong", 10000, 1234); //카드번호, 계좌번호, 이름, 액수, 비밀번호
    Account Kim_chul_su_01(3301, 2222, "Kim chulsu", 10000, 1234);
    Account Park_min_su_01(1111, 3333, "Park minsu", 10000, 1234);
    Account Kim_yu_ri_01(3311, 4444, "Kim yuri", 10000, 1234);
    Account Park_bo_gyung_01(1121, 5555, "Park bogyung", 10000, 1234);
    Account Hong_gil_dong_02(3321, 6666, "Hong gildong", 10000, 1234);
    Account* accarr[] = { &Hong_gil_dong_01, &Kim_chul_su_01, &Park_min_su_01, &Kim_yu_ri_01, &Park_bo_gyung_01, &Hong_gil_dong_02 };
    // 여기서, 배열을 포인터 배열이 아닌 그냥 객체의 배열로 하면 모든 오브젝트가 배열에 "복사" 된다!!
    //   -> 곧 address 도 바뀐다는 것을 항상 명심하자!!
    int accarr_len = sizeof accarr / sizeof accarr[0];      // 시간이 나면 main 함수에서 account의 배열을 따로 정의할 필요가 없게 만들어보자

    //Account의 cardnum을 각 은행에 저장     ----------------> 나중에 나머지에 따라서 각 은행으로 들어가도록 해야함
    for (int i = 0; i < accarr_len; i++) {
        if (accarr[i]->get_Cardnum() % 100 == 1) {    // Account 객체의 Cardnum을 100으로 나눈 나머지가 1이면 DaeguBank에
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

    //각 Bank에 Account 연결
    for (int i = 0; i < accarr_len; i++)                  // Account 객체가 생성되자마자 자동으로 pAcclist에 들어가게 만들 수는 없을까?
        if (accarr[i]->get_Cardnum() % 100 == 1) {         // Account 객체의 Cardnum을 100으로 나눈 나머지가 1이면 DaeguBank에
            DaeguBank.addAcclist(accarr[i]);
        }
        else if (accarr[i]->get_Cardnum() % 100 == 11) {   // '''''' 나머지가 11 이면 SamsungBank에
            SamsungBank.addAcclist(accarr[i]);
        }
        else if (accarr[i]->get_Cardnum() % 100 == 21) {   // '''''' 나머지가 21 이면 KakaoBank에 들어간다.
            KakaoBank.addAcclist(accarr[i]);
        }

    // 가장 첫 화면
    int ATM_cnt;
    while (true) {
        Sleep(2000);
        system("cls");//콘솔 화면 초기화
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
            if (ATM_cnt < 0 || ATM_cnt>7)
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
            // 여기서부터 ATM start를 통해서 시작 

            //cout << "Please insert your card(Enter your card number)" << endl;
            int card_num;
            //cin >> card_num;
            cout << endl;
            int card_index = -1;
            int password;
            auto current_bank = &Bank;          // 일단 Bank* 타입으로 정의하고 밑에서 다운캐스팅을 한다
            string current_bank_str = "";

            int Cnt_withdrawal = 0; // 출금 횟수 정해서 예외처리
            // GUI를 class로 할건지 그냥 main에 쓸건지 --> 둘다 상관은 없을 것 같지만 나중에 가독성 보고 고려
            while (true) {
            tryAgain:
                Sleep(3000);
                system("cls");//콘솔 화면 초기화
                cout << "┌-----------------------------------------------------┐" << endl;
                cout << "│                      " << start->get_ATMBank() << endl;
                cout << "├-----------------------------------------------------┤" << endl;
                cout << "│ What do you want to do ? Please press number(ex. 1)" << endl;
                cout << "│ 0. Stop using (Go back ATM_list display)" << endl;
                cout << "│ 1. Cancel" << endl;
                cout << "│ 2. Card insert" << endl;
                cout << "│ 3. Receipt Print" << endl;
                cout << "│ 4. Deposit" << endl;
                cout << "│ 5. Withdrawal" << endl;
                cout << "│ 6. Transfer" << endl;
                cout << "├-----------------------------------------------------┤" << endl;
                cout << "│   ┌------------------┐        ①②③" << endl;
                cout << "│";
                if (card_index == -1)  cout << "   │    input card    │        ⑤⑥⑦" << endl;
                else cout << "   │ =================│        ⑤⑥⑦" << endl;
                cout << "│   └------------------┘        ⑦⑧⑨" << endl;
                cout << "└-----------------------------------------------------┘" << endl;

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
                    card_index = -1;
                    cout << "Please get a card" << endl;
                    continue;
                }
                else if (press_button == 2) {                              // 카드 재입력
                    try {
                        if (card_index == -1) {
                            cout << "Please insert your card(Enter your card number)" << endl;
                            cin >> card_num;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            if (card_num % 100 == 1) {                        // card valid 검사
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

                            if (start->get_ATMSingle() == true) {        // 카드 valid 검사 직후 ATM 싱글/멀티 체크 -> 탈락 시 throw -> continue
                                if (start->get_ATMBankname() != current_bank_str) {
                                    card_index = -1;
                                    throw exception("This card is not supported by this ATM machine");
                                }
                                else                                     // 지원하는 경우에도 문구 출력
                                    cout << "This card is useable on this ATM machine" << endl;
                            }
                            else
                                cout << "This card is useable on this ATM machine" << endl; // 지원하는 경우에도 문구 출력

                            Account* Acc_password = current_bank->get_Account()[card_index];
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
                                    if (password != Acc_password->getPassword()) {
                                        cout << "Wrong Password" << endl;
                                        throw password;

                                    }

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
                                cout << "Please get a card" << endl;
                                card_index = -1;
                                continue;
                            }
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
                    //여기서 Deposit 수행
                    Account* Acc_deposit = current_bank->get_Account()[card_index];

                    int One_thousand_won = 0;
                    int Five_thousand_won = 0;
                    int Ten_tousand_won = 0;
                    int Fifty_thousand_won = 0;
                    int check = 0;




                    string ATMBankname1 = start->get_ATMBankname();
                    int deposit_fee = start->Howmuchfee(ATMBankname1, current_bank_str, "Depos");
                    while (true) {
                        try {
                            cout << "Enter the Enter the number of one_thousand won to deposit: ";
                            cin >> One_thousand_won;
                            if (cin.fail() || One_thousand_won < 0) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            cout << "Enter the Enter the number of five_thousand won to deposit: ";
                            cin >> Five_thousand_won;
                            if (cin.fail() || Five_thousand_won < 0) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            cout << "Enter the Enter the number of ten_thousand won to deposit: ";
                            cin >> Ten_tousand_won;
                            if (cin.fail() || Ten_tousand_won < 0) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            cout << "Enter the Enter the number of fifty_thousand won to deposit: ";
                            cin >> Fifty_thousand_won;
                            if (cin.fail() || Fifty_thousand_won < 0) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            cout << "Enter the Enter the number of check to deposit: ";
                            cin >> check;
                            if (cin.fail() || check < 0) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }


                            int deposit_money = 1000 * One_thousand_won + 5000 * Five_thousand_won + 10000 * Ten_tousand_won + 50000 * Fifty_thousand_won;

                            if (deposit_money + 100000 * check < deposit_fee)
                                throw exception("Deposited money is smaller than the fee.");      // 입금 금액이 수수료보다 작을 시 다시 입금

                            int atm_num_of_cash = One_thousand_won + Five_thousand_won + Ten_tousand_won + Fifty_thousand_won;
                            if (atm_num_of_cash > start->get_ATM_num_of_cash() || check > start->get_ATM_num_of_check()) {
                                throw exception("You have exceeded the amount of money(cash or check) you can deposit.");
                            }
                            break;
                        }
                        catch (exception& e) {
                            try {
                                int next_button;
                                cout << e.what() << endl;
                                cout << "Are you sure you want to re-enter?" << endl;
                                cout << "1. Yes    2. No" << endl;
                                cin >> next_button;
                                if (next_button == 1) {
                                    continue;
                                }
                                else {
                                    throw exception("Go to start screen");
                                }

                            }
                            catch (exception& e) {
                                goto tryAgain;
                            }

                        }
                    }

                    // Howmuchfee(string pa_ATMBankname, string pa_current_bank_str, string pa_transaction)


                    int deposit_money = 1000 * One_thousand_won + 5000 * Five_thousand_won + 10000 * Ten_tousand_won + 50000 * Fifty_thousand_won;
                    start->change_ATMmoney(deposit_money);
                    Acc_deposit->change_Money(deposit_money - deposit_fee + 100000 * check);
                    start->add_history(Acc_deposit->get_Username() + " deposit $" + to_string(deposit_money) + "\n");

                    cout << "Deposit fee is : " << deposit_fee << endl;
                    cout << Acc_deposit->get_Username() << "'s money : " << Acc_deposit->HowMoney() << endl;
                    cout << "ATM money : " << DaeguATM.get_ATMmoney() << endl;

                    // 이하 디버깅 코드는 나중에 지우자

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

                    if (Cnt_withdrawal >= 3) {
                        cout << "The maximum number of withdrawals has been exceeded." << endl;
                        continue;
                    }
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
                            if (withdrawal_money % 1000 != 0) {
                                throw exception("Withdrawal is possible only in units of 1,000 won.");
                            }
                            if (withdrawal_money < 0)
                                throw exception("Out of range!");
                            if (withdrawal_money + withdrawl_fee > Acc_withdrawal->HowMoney())
                                throw exception("There is not enough balance in your account.");
                            if (withdrawal_money > start->get_ATMmoney()) {
                                throw exception("There is not enough balance in ATM machine.");
                            }
                            break;
                        }
                        catch (exception& e) {
                            try {
                                int next_button;
                                cout << e.what() << endl;
                                cout << "Are you sure you want to re-enter?" << endl;
                                cout << "1. Yes    2. No" << endl;
                                cin >> next_button;
                                if (next_button == 1) {
                                    continue;
                                }
                                else {
                                    throw exception("Go to start screen");
                                }

                            }
                            catch (exception& e) {
                                goto tryAgain;
                            }

                        }
                    }
                    Cnt_withdrawal += 1;
                    cout << Cnt_withdrawal;
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
                    //여기서 Transfer 수행
                    Account* Acc_send = current_bank->get_Account()[card_index];
                    int transfer_money;
                    string ATMBankname1 = start->get_ATMBankname();
                    int transfer_button;

                    int transfer_card;
                    auto current_tbank = &Bank;
                    string current_tbank_str = "";
                    int transfer_fee = 0;
                    Account* Acc_get = current_bank->get_Account()[card_index];    // 초기화 위해서 

                    while (true) {
                        try {
                            cout << "Select cash transfer or account fund transfer." << endl;
                            cout << "1. Cash transfer      2. Account fund transfer" << endl;

                            cin >> transfer_button;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            if (transfer_button < 1 || transfer_button>2)
                                throw exception("Out of range!");

                            if (transfer_button == 2) {
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

                            else if (transfer_button == 1) {
                                cout << "Enter the money you want to transfer" << endl;
                                cin >> transfer_money;
                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore(100, '\n');
                                    throw exception("Value error!");
                                }
                                if (transfer_money < 0)
                                    throw exception("Out of range!");

                            }
                            else {
                                throw exception("Value error!");
                            }

                            cout << "Please enter the card number of the recipient" << endl;
                            cin >> transfer_card;;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw exception("Value error!");
                            }
                            if (card_num == transfer_card)
                                throw exception("This is same card");
                            if (transfer_card % 100 == 1) {                        // card valid 검사
                                if (DaeguBank.find_card(transfer_card) == -1)
                                    throw exception("This card is not valid");
                                cout << "Card is valid" << endl;
                                current_tbank = &DaeguBank;
                                current_tbank_str = "DaeguBank";

                            }
                            else if (transfer_card % 100 == 11) {
                                if (SamsungBank.find_card(transfer_card) == -1)
                                    throw exception("This card is not valid");
                                cout << "Card is valid" << endl;
                                current_tbank = &SamsungBank;
                                current_tbank_str = "SamsungBank";

                            }
                            else if (transfer_card % 100 == 21) {
                                if (KakaoBank.find_card(transfer_card) == -1)
                                    throw exception("This card is not valid");
                                cout << "Card is valid" << endl;
                                current_tbank = &KakaoBank;
                                current_tbank_str = "KakaoBank";

                            }
                            else
                                throw exception("This card is not valid");

                            if (transfer_button == 2) {
                                transfer_fee = start->Howmuchfee(ATMBankname1, current_bank_str, current_tbank_str, "Trans");
                                Acc_get = current_tbank->get_Account()[current_tbank->find_card(transfer_card)];
                                if (Acc_send->HowMoney() < transfer_money + transfer_fee) {
                                    throw exception("There is no enough money");
                                }
                                Acc_send->change_Money(-transfer_money - transfer_fee);
                                Acc_get->change_Money(transfer_money);
                                start->add_history(Acc_send->get_Username() + " transfer $" + to_string(transfer_money) + " to " + Acc_get->get_Username() + "\n");
                                break;
                            }
                            else if (transfer_button == 1) {
                                transfer_fee = start->Howmuchfee(ATMBankname1, current_tbank_str, "Trans");
                                Acc_get = current_tbank->get_Account()[current_tbank->find_card(transfer_card)];
                                if (transfer_money < transfer_fee) {
                                    throw exception("There is no enough money");
                                }
                                Acc_get->change_Money(transfer_money - transfer_fee);
                                start->change_ATMmoney(transfer_money);
                                start->add_history(Acc_send->get_Username() + " transfer $" + to_string(transfer_money) + " to " + Acc_get->get_Username() + "\n");
                                break;

                            }

                            else {
                                throw exception("Value Error!");
                            }
                        }

                        catch (exception& e) {
                            try {
                                int next_button;
                                cout << e.what() << endl;
                                cout << "Are you sure you want to re-enter?" << endl;
                                cout << "1. Yes    2. No" << endl;
                                cin >> next_button;
                                if (next_button == 1) {
                                    continue;
                                }
                                else {
                                    throw exception("Go to start screen");
                                }

                            }
                            catch (exception& e) {
                                goto tryAgain;
                            }
                        }
                    }

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