#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <windows.h>
#include <fstream>
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
    int ATMmoney;
    bool Single;
    int num_of_deposit_cash;
    int num_of_deposit_check;

    string History;
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

    ATM();
    ATM(int pa_ATMnum, string pa_ATMBank, string pa_ATMBankname, bool pa_SinorMul) {
        ATMnum = pa_ATMnum;
        ATMBank = pa_ATMBank;
        ATMBankname = pa_ATMBankname;
        ATMmoney = 10000000;
        Single = pa_SinorMul;
        num_of_deposit_cash = 25;
        num_of_deposit_check = 10;
    }
    ~ATM() {}
};

ATM::ATM() : ATMnum(0), ATMBank("None"), ATMmoney(10000000), Single(true), History(nullptr), p_AccountNum(nullptr), p_UserName(nullptr), num_of_deposit_cash(25), num_of_deposit_check(10) {}// 모든 멤버를 디폴트 값으로 생성

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
    Bank Bank;
    Daegu_Bank DaeguBank;
    Samsung_Bank SamsungBank;
    Kakao_Bank KakaoBank;

    // ATM 초기화
    ATM DaeguATM(11, "Daegu ATM", "DaeguBank", false);  //일련번호, ATM 이름, ATM의 소속 은행, multi-bank 지원 가능 여부
    ATM DaeguATM_sin(12, "Daegu ATM (DaeguBank only)", "DaeguBank", true);
    ATM SamsungATM(21, "Samsung ATM", "SamsungBank", false);
    ATM SamsungATM_sin(22, "Samsung ATM (SamsungBank only)", "SamsungBank", true);
    ATM KakaoATM(31, "Kakao ATM", "KakaoBank", false);
    ATM KakaoATM_sin(32, "Kakao ATM (KakaoBank only)", "KakaoBank", true);
    ATM atmarr[] = { DaeguATM, DaeguATM_sin, SamsungATM, SamsungATM_sin, KakaoATM, KakaoATM_sin };
    int atmarr_len = sizeof atmarr / sizeof atmarr[0];

    //Bank에 ATM 연결

    Bank.addATMlist(&DaeguATM);
    Bank.addATMlist(&DaeguATM_sin);
    Bank.addATMlist(&SamsungATM);
    Bank.addATMlist(&SamsungATM_sin);
    Bank.addATMlist(&KakaoATM);
    Bank.addATMlist(&KakaoATM_sin);

    //Account 초기화, Admin card는 9999
    Account Hong_gil_dong_01(1101, 1111, "Hong gildong", 10000, 1234); //카드번호, 계좌번호, 이름, 액수, 비밀번호
    Account Kim_chul_su_01(3301, 2222, "Kim chulsu", 10000, 1234);
    Account Park_min_su_01(1111, 3333, "Park minsu", 10000, 1234);
    Account Kim_yu_ri_01(3311, 4444, "Kim yuri", 10000, 1234);
    Account Park_bo_gyung_01(1121, 5555, "Park bogyung", 10000, 1234);
    Account Hong_gil_dong_02(3321, 6666, "Hong gildong", 10000, 1234);
    Account* accarr[] = { &Hong_gil_dong_01, &Kim_chul_su_01, &Park_min_su_01, &Kim_yu_ri_01, &Park_bo_gyung_01, &Hong_gil_dong_02 };
    int accarr_len = sizeof accarr / sizeof accarr[0];

    //Account의 cardnum을 100의 나머지에 따라서 각 은행에 저장
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
    for (int i = 0; i < accarr_len; i++)
        if (accarr[i]->get_Cardnum() % 100 == 1) {         // Account 객체의 Cardnum을 100으로 나눈 나머지가 1이면 DaeguBank에
            DaeguBank.addAcclist(accarr[i]);
        }
        else if (accarr[i]->get_Cardnum() % 100 == 11) {   // '''''' 나머지가 11 이면 SamsungBank에
            SamsungBank.addAcclist(accarr[i]);
        }
        else if (accarr[i]->get_Cardnum() % 100 == 21) {   // '''''' 나머지가 21 이면 KakaoBank에 들어간다.
            KakaoBank.addAcclist(accarr[i]);
        }

    int KorEng = 0;     // 한/영 전환 indicator
                        // 한/영 전환은 ATM 선택 후부터

    // 가장 첫 화면
    int ATM_cnt;
    while (true) {
        system("cls");//콘솔 화면 초기화
        cout << "Please press your ATM number(ex. 1)" << endl;
        cout << endl;
        cout << "0: Quit session" << endl;
        cout << endl;
        for (int i = 0; i < atmarr_len; i++) {
            cout << i + 1 << ". " << (atmarr + i)->get_ATMBank() << " " << endl;
        }
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
            continue;
        }

        if (ATM_cnt == 0) {
            break;
        }

        else {

            ATM* start = Bank.get_ATM()[ATM_cnt - 1];
            cout << endl;
            cout << "Start Banking : " << start->get_ATMBank() << endl;

            // 여기서부터 ATM start를 통해서 시작 

            int card_num = 0;
            cout << endl;
            int card_index = -1;
            int password;
            auto current_bank = &Bank;          // Bank* 타입으로 정의하고 밑에서 다운캐스팅을 한다
            string current_bank_str = "";

            int history_id = 0;
            string user_history = "";

            int Cnt_withdrawal = 0; // 출금 횟수 정해서 예외처리
            while (true) {
            tryAgain:
                system("cls");//콘솔 화면 초기화
                if (KorEng % 2 == 0) {
                    cout << "┌-----------------------------------------------------┐" << endl;
                    cout << "│                      " << start->get_ATMBank() << endl;
                    cout << "├-----------------------------------------------------┤" << endl;
                    cout << "│ What do you want to do ? Please press number(ex. 1)" << endl;
                    cout << "│ 0. Admin Menu" << endl;//card_num == 9999
                    cout << "│ 1. Cancel" << endl;
                    cout << "│ 2. Card insert" << endl;
                    cout << "│ 3. Receipt Print" << endl;
                    cout << "│ 4. Deposit" << endl;
                    cout << "│ 5. Withdrawal" << endl;
                    cout << "│ 6. Transfer" << endl;
                    (ATM_cnt % 2 == 1) ? cout << "│ 7. Language Conversion : Korean / English" << endl : cout << "";
                    cout << "│ 10. Stop using (Go back ATM_list display)" << endl;
                    cout << "├-----------------------------------------------------┤" << endl;
                    cout << "│   ┌------------------┐        ①②③" << endl;
                    cout << "│";
                    if (card_index == -1 && card_num != 9999)  cout << "   │    input card    │        ⑤⑥⑦" << endl;
                    else cout << "   │ =================│        ⑤⑥⑦" << endl;
                    cout << "│   └------------------┘        ⑦⑧⑨" << endl;
                    cout << "└-----------------------------------------------------┘" << endl;
                }
                else if (KorEng % 2 == 1) {
                    cout << "┌-----------------------------------------------------┐" << endl;
                    cout << "│                      " << start->get_ATMBank() << endl;
                    cout << "├-----------------------------------------------------┤" << endl;
                    cout << "│ 어떤 작업을 원하시나요 ? 버튼을 눌러주세요(예시: 1)" << endl;
                    cout << "│ 0. 관리자 설정" << endl;
                    cout << "│ 1. 카드 반환" << endl;
                    cout << "│ 2. 카드 삽입" << endl;
                    cout << "│ 3. 영수증 출력" << endl;
                    cout << "│ 4. 입금" << endl;
                    cout << "│ 5. 출금" << endl;
                    cout << "│ 6. 송금" << endl;
                    (ATM_cnt % 2 == 1) ? cout << "│ 7. 언어 변경 : 한국어 / 영어" << endl : cout << "";
                    cout << "│ 10. 사용 중지(ATM 선택 화면으로 돌아갑니다)" << endl;
                    cout << "├-----------------------------------------------------┤" << endl;
                    cout << "│   ┌------------------┐        ①②③" << endl;
                    cout << "│";
                    if (card_index == -1 && card_num != 9999)  cout << "   │     카드 삽입    │        ⑤⑥⑦" << endl;
                    else cout << "   │ =================│        ⑤⑥⑦" << endl;
                    cout << "│   └------------------┘        ⑦⑧⑨" << endl;
                    cout << "└-----------------------------------------------------┘" << endl;
                }
                int press_button;
                try {
                    cin >> press_button;
                    if (press_button == 10) {//ATM 종료
                        (KorEng % 2 == 0) ? cout << "Thank you for using ATM" << endl : cout << "ATM을 이용해주셔서 감사합니다" << endl;
                        KorEng = 0;   // ATM 선택 시 처음 출력되는 언어는 영어로 고정!
                        Sleep(2000);
                        break;
                    }
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(100, '\n');
                        (KorEng % 2 == 0) ? throw exception("Value error!") : throw exception("입력 오류!");
                    }
                    if (ATM_cnt % 2 == 0) {
                        if (press_button < 0 || press_button>6)
                            (KorEng % 2 == 0) ? throw exception("Out of range!") : throw exception("범위 초과!");
                    }
                    else if (ATM_cnt % 2 == 1) {
                        if (press_button < 0 || press_button>7)
                            (KorEng % 2 == 0) ? throw exception("Out of range!") : throw exception("범위 초과!");
                    }
                    // 카드를 안 넣어도 언어 변환은 할 수 있게
                    if (press_button != 7) {
                        if (card_index == -1 && (press_button < 0 || press_button > 2)) {
                            if (card_num == 9999)//관리자 카드 예외
                                (KorEng % 2 == 0) ? throw exception("Admin card can't use this option!") : throw exception("관리자 카드는 사용할 수 없는 기능입니다!");
                            else//카드가 입력되지 않으면 카드 입력 외 다른 메뉴 사용불가 
                                (KorEng % 2 == 0) ? throw exception("No card input") : throw exception("입력된 카드가 없습니다.");
                        }
                    }
                }
                catch (exception& e) {
                    cout << e.what() << endl;
                    Sleep(2000);
                    continue;
                }

                cout << endl;
                if (press_button == 1) {
                    user_history = "";
                    card_index = -1;
                    card_num = -1;
                    (KorEng % 2 == 0) ? cout << "Please get a card" << endl : cout << "카드를 받아주세요" << endl;
                }
                else if (press_button == 2) {   // 카드 재입력
                    try {
                        if (card_index == -1) {
                            (KorEng % 2 == 0) ? cout << "Please insert your card(Enter your card number)" << endl : cout << "카드를 삽입해주세요(카드 번호를 입력해주세요)" << endl;
                            cin >> card_num;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                (KorEng % 2 == 0) ? throw exception("Value error!") : throw exception("입력 오류!");
                            }
                            if (card_num == 9999) {
                                (KorEng % 2 == 0) ? cout << "Admin card!" << endl : cout << "관리자 카드입니다." << endl;
                                Sleep(2000);
                                continue;
                            }
                            else if (card_num % 100 == 1) {       // card valid 검사                 
                                if (DaeguBank.find_card(card_num) == -1)
                                    (KorEng % 2 == 0) ? throw exception("This card is not valid") : throw exception("유효하지 않은 카드입니다");
                                (KorEng % 2 == 0) ? cout << "Card is valid" << endl : cout << "유효한 카드입니다" << endl;
                                card_index = DaeguBank.find_card(card_num);
                                current_bank = &DaeguBank;
                                current_bank_str = "DaeguBank";
                            }
                            else if (card_num % 100 == 11) {
                                if (SamsungBank.find_card(card_num) == -1)
                                    (KorEng % 2 == 0) ? throw exception("This card is not valid") : throw exception("유효하지 않은 카드입니다");
                                (KorEng % 2 == 0) ? cout << "Card is valid" << endl : cout << "유효한 카드입니다" << endl;
                                card_index = SamsungBank.find_card(card_num);
                                current_bank = &SamsungBank;
                                current_bank_str = "SamsungBank";
                            }
                            else if (card_num % 100 == 21) {
                                if (KakaoBank.find_card(card_num) == -1)
                                    (KorEng % 2 == 0) ? throw exception("This card is not valid") : throw exception("유효하지 않은 카드입니다");
                                (KorEng % 2 == 0) ? cout << "Card is valid" << endl : cout << "유효한 카드입니다" << endl;
                                card_index = KakaoBank.find_card(card_num);
                                current_bank = &KakaoBank;
                                current_bank_str = "KakaoBank";
                            }
                            else
                                (KorEng % 2 == 0) ? throw exception("This card is not valid") : throw exception("유효하지 않은 카드입니다");

                            if (start->get_ATMSingle() == true) {        // 카드 valid 검사 직후 ATM 싱글/멀티 체크 -> 탈락 시 throw -> continue
                                if (start->get_ATMBankname() != current_bank_str) {
                                    card_index = -1;
                                    (KorEng % 2 == 0) ? throw exception("This card is not supported by this ATM machine") : throw exception("이 카드는 해당 ATM에서 사용하실 수 없습니다");
                                }
                                else                                     // 지원하는 경우에도 문구 출력
                                    (KorEng % 2 == 0) ? cout << "This card is useable on this ATM machine" << endl : cout << "이 카드는 해당 ATM에서 사용하실 수 있습니다" << endl;
                            }
                            else
                                (KorEng % 2 == 0) ? cout << "This card is useable on this ATM machine" << endl : cout << "이 카드는 해당 ATM에서 사용하실 수 있습니다" << endl;

                            Account* Acc_password = current_bank->get_Account()[card_index];
                            int i;
                            for (i = 0; i < 3; i++) {
                                try {
                                    (KorEng % 2 == 0) ? cout << "Enter your password" << endl : cout << "비밀번호를 입력해주세요" << endl;
                                    cin >> password;
                                    if (cin.fail()) {
                                        cin.clear();
                                        cin.ignore(100, '\n');
                                        (KorEng % 2 == 0) ? throw exception("Wrong Password") : throw exception("비밀번호가 틀렸습니다");
                                    }
                                    if (password != Acc_password->getPassword()) {
                                        (KorEng % 2 == 0) ? cout << "Wrong Password" << endl : cout << "비밀번호가 틀렸습니다" << endl;
                                        throw password;

                                    }

                                    break;
                                }
                                catch (exception& e) {
                                    cout << e.what() << endl;
                                    (KorEng % 2 == 0) ? cout << "Password error : " << i + 1 << "times" << endl : cout << "비밀번호 입력 오류 : " << i + 1 << "회" << endl;
                                    continue;
                                }
                                catch (int t) {
                                    (KorEng % 2 == 0) ? cout << "Password error : " << i + 1 << "times" << endl : cout << "비밀번호 입력 오류 : " << i + 1 << "회" << endl;
                                }

                            }
                            if (i == 3) {
                                (KorEng % 2 == 0) ? cout << "too many error" << endl : cout << "비밀번호를 너무 많이 틀렸습니다" << endl;
                                (KorEng % 2 == 0) ? cout << "Please get a card" << endl : cout << "카드를 받아주세요" << endl;
                                card_index = -1;
                                Sleep(2000);
                                continue;
                            }
                        }
                        else {
                            (KorEng % 2 == 0) ? cout << "A card is already inserted." << endl : cout << "카드가 이미 삽입되어 있습니다" << endl;
                            (KorEng % 2 == 0) ? cout << "If you want to work with another card, press button '1'." << endl : cout << "다른 카드를 사용하고 싶으시면, 1번 버튼을 눌러주세요" << endl;
                        }

                    }
                    catch (exception& e) {
                        cout << e.what() << endl;
                        Sleep(2000);
                        continue;
                    }
                }
                else if (press_button == 3) {
                    (KorEng % 2 == 0) ? cout << "Receipt:" << endl : cout << "영수증:" << endl;
                    cout << user_history << endl;
                }
                else if (press_button == 4) {
                    Account* Acc_deposit = current_bank->get_Account()[card_index];

                    int One_thousand_won = 0;
                    int Five_thousand_won = 0;
                    int Ten_tousand_won = 0;
                    int Fifty_thousand_won = 0;
                    int check = 0;

                    string ATMBankname1 = start->get_ATMBankname();
                    int deposit_fee = start->Howmuchfee(ATMBankname1, current_bank_str, "Depos");
                    while (true) {//여기서 Deposit 수행
                        try {
                            (KorEng % 2 == 0) ? cout << "Enter the Enter the number of one_thousand won to deposit: " : cout << "입금하실 천원 지폐의 개수를 입력해주세요: ";
                            cin >> One_thousand_won;
                            if (cin.fail() || One_thousand_won < 0) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                (KorEng % 2 == 0) ? throw exception("Value error!") : throw exception("입력 오류!");
                            }
                            (KorEng % 2 == 0) ? cout << "Enter the Enter the number of five_thousand won to deposit: " : cout << "입금하실 오천원 지폐의 개수를 입력해주세요: ";
                            cin >> Five_thousand_won;
                            if (cin.fail() || Five_thousand_won < 0) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                (KorEng % 2 == 0) ? throw exception("Value error!") : throw exception("입력 오류!");
                            }
                            (KorEng % 2 == 0) ? cout << "Enter the Enter the number of ten_thousand won to deposit: " : cout << "입금하실 만원 지폐의 개수를 입력해주세요: ";
                            cin >> Ten_tousand_won;
                            if (cin.fail() || Ten_tousand_won < 0) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                (KorEng % 2 == 0) ? throw exception("Value error!") : throw exception("입력 오류!");
                            }
                            (KorEng % 2 == 0) ? cout << "Enter the Enter the number of fifty_thousand won to deposit: " : cout << "입금하실 오만원 지폐의 개수를 입력해주세요: ";
                            cin >> Fifty_thousand_won;
                            if (cin.fail() || Fifty_thousand_won < 0) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                (KorEng % 2 == 0) ? throw exception("Value error!") : throw exception("입력 오류!");
                            }
                            (KorEng % 2 == 0) ? cout << "Enter the Enter the number of check to deposit: " : cout << "입금하실 수표의 개수를 입력해주세요: ";
                            cin >> check;
                            if (cin.fail() || check < 0) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                (KorEng % 2 == 0) ? throw exception("Value error!") : throw exception("입력 오류!");
                            }


                            int deposit_money = 1000 * One_thousand_won + 5000 * Five_thousand_won + 10000 * Ten_tousand_won + 50000 * Fifty_thousand_won;

                            if (deposit_money + 100000 * check < deposit_fee)
                                (KorEng % 2 == 0) ? throw exception("Deposited money is smaller than the fee.") : throw exception("입금된 액수가 수수료보다 작습니다");
                            // 입금 금액이 수수료보다 작을 시 다시 입금

                            int atm_num_of_cash = One_thousand_won + Five_thousand_won + Ten_tousand_won + Fifty_thousand_won;
                            if (atm_num_of_cash > start->get_ATM_num_of_cash() || check > start->get_ATM_num_of_check()) {
                                (KorEng % 2 == 0) ? throw exception("You have exceeded the amount of money(cash or check) you can deposit.") : throw exception("입금 가능한 현금 혹은 수표의 액수를 초과하셨습니다");
                            }
                            break;
                        }
                        catch (exception& e) {
                            try {
                                int next_button;
                                cout << e.what() << endl;
                                (KorEng % 2 == 0) ? cout << "Are you sure you want to re-enter?" << endl : cout << "정말 종료하시겠습니까?" << endl;
                                (KorEng % 2 == 0) ? cout << "1. Yes    2. No" << endl : cout << "1. 네    2. 아니오" << endl;
                                cin >> next_button;
                                if (next_button == 1) {
                                    continue;
                                }
                                else {
                                    (KorEng % 2 == 0) ? throw exception("Go to start screen") : throw exception("초기 화면으로 돌아갑니다");
                                }

                            }
                            catch (exception& e) {
                                goto tryAgain;
                            }

                        }
                    }

                    int deposit_money = 1000 * One_thousand_won + 5000 * Five_thousand_won + 10000 * Ten_tousand_won + 50000 * Fifty_thousand_won;
                    start->change_ATMmoney(deposit_money);
                    Acc_deposit->change_Money(deposit_money - deposit_fee + 100000 * check);
                    string k;
                    (KorEng % 2 == 0) ? k = " deposit $" : k = " 입금 $";
                    user_history += Acc_deposit->get_Username() + k + to_string(deposit_money - deposit_fee + 100000 * check) + "\n";
                    cout << endl << Acc_deposit->get_Username() + k + to_string(deposit_money - deposit_fee + 100000 * check) + "\n";
                    start->add_history("ID: " + to_string(history_id) + " Card number: " + to_string(card_num) + " History: " + Acc_deposit->get_Username() + " deposit $" + to_string(deposit_money) + "\n");
                    history_id++;

                    (KorEng % 2 == 0) ? cout << "Deposit fee is : " << deposit_fee << endl : cout << "입금 수수료 : " << deposit_fee << endl;
                    (KorEng % 2 == 0) ? cout << Acc_deposit->get_Username() << "'s money : " << Acc_deposit->HowMoney() << endl : cout << Acc_deposit->get_Username() << "님의 잔액 : " << Acc_deposit->HowMoney() << endl;
                    // 영어 변수 1
                    (KorEng % 2 == 0) ? cout << "ATM money : " << start->get_ATMmoney() << endl : cout << "ATM 기기에 남은 현금 : " << start->get_ATMmoney() << endl;

                    cout << endl;
                }
                else if (press_button == 5) {
                    try {
                        if (Cnt_withdrawal >= 3) {
                            (KorEng % 2 == 0) ? throw exception("The maximum number of withdrawals has been exceeded.") : throw exception("출금 가능한 횟수를 초과하셨습니다");
                        }
                    }
                    catch (exception& e) {
                        try {
                            int next_button;
                            cout << e.what() << endl;
                            (KorEng % 2 == 0) ? cout << "Are you sure you want to re-enter?" << endl : cout << "정말 종료하시겠습니다?" << endl;
                            (KorEng % 2 == 0) ? cout << "1. Yes    2. No" << endl : cout << "1. 네    2. 아니오" << endl;
                            cin >> next_button;
                            if (next_button == 1)
                                continue;
                            else
                                (KorEng % 2 == 0) ? throw exception("Go to start screen") : throw exception("초기 화면으로 돌아갑니다");
                        }
                        catch (exception& e) {
                            goto tryAgain;
                        }
                    }
                    int withdrawal_money;
                    Account* Acc_withdrawal = current_bank->get_Account()[card_index];
                    string ATMBankname1 = start->get_ATMBankname();
                    int withdrawl_fee = start->Howmuchfee(ATMBankname1, current_bank_str, "Withd");
                    while (true) {
                        try {
                            (KorEng % 2 == 0) ? cout << "Enter the money you want to withdrawal" << endl : cout << "출금하실 금액을 입력해주세요" << endl;
                            cin >> withdrawal_money;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                (KorEng % 2 == 0) ? throw exception("Value error!") : throw exception("입력 오류!");
                            }
                            if (withdrawal_money % 1000 != 0)
                                (KorEng % 2 == 0) ? throw exception("Withdrawal is possible only in units of 1,000 won.") : throw exception("출금은 1000원 단위만 가능합니다");
                            if (withdrawal_money > start->get_ATMmoney())
                                (KorEng % 2 == 0) ? throw exception("There is not enough balance in ATM machine.") : throw exception("ATM 기기의 현금 잔고가 부족합니다");
                            if (withdrawal_money + withdrawl_fee > Acc_withdrawal->HowMoney())
                                (KorEng % 2 == 0) ? throw exception("There is not enough balance in your account.") : throw exception("잔액이 부족합니다");
                            if (withdrawal_money < 0 || withdrawal_money>500000)
                                (KorEng % 2 == 0) ? throw exception("Out of range!") : throw exception("범위 초과!");
                            break;
                        }
                        catch (exception& e) {
                            try {
                                int next_button;
                                cout << e.what() << endl;
                                (KorEng % 2 == 0) ? cout << "Are you sure you want to re-enter?" << endl : cout << "정말 종료하시겠습니다?" << endl;
                                (KorEng % 2 == 0) ? cout << "1. Yes    2. No" << endl : cout << "1. 네    2. 아니오" << endl;
                                cin >> next_button;
                                if (next_button == 1)
                                    continue;
                                else
                                    (KorEng % 2 == 0) ? throw exception("Go to start screen") : throw exception("초기 화면으로 돌아갑니다");
                            }
                            catch (exception& e) {
                                goto tryAgain;
                            }
                        }
                    }
                    Cnt_withdrawal += 1;
                    (KorEng % 2 == 0) ? cout << endl << "Remaning num: " << 3 - Cnt_withdrawal : cout << endl << "남은 횟수: " << 3 - Cnt_withdrawal;
                    start->change_ATMmoney(-withdrawal_money);
                    Acc_withdrawal->change_Money(-withdrawal_money - withdrawl_fee);
                    string k;
                    (KorEng % 2 == 0) ? k = " withdrawal $" : k = " 출금 $";
                    user_history += Acc_withdrawal->get_Username() + k + to_string(withdrawal_money) + "\n";
                    start->add_history("ID: " + to_string(history_id) + " Card number: " + to_string(card_num) + " History: " + Acc_withdrawal->get_Username() + " withdrawal $" + to_string(withdrawal_money) + "\n");
                    history_id++;

                    cout << endl << Acc_withdrawal->get_Username() + k + to_string(withdrawal_money) + "\n";
                    (KorEng % 2 == 0) ? cout << "Withdrawl fee is : " << withdrawl_fee << endl : cout << "출금 수수료 : " << withdrawl_fee << endl;
                    (KorEng % 2 == 0) ? cout << Acc_withdrawal->get_Username() << "'s money : " << Acc_withdrawal->HowMoney() << endl : cout << Acc_withdrawal->get_Username() << "님의 잔액 : " << Acc_withdrawal->HowMoney() << endl;
                    (KorEng % 2 == 0) ? cout << "ATM money : " << start->get_ATMmoney() << endl : cout << "ATM 기기에 남은 현금 : " << start->get_ATMmoney() << endl;

                    cout << endl;
                }
                else if (press_button == 6) {
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
                            (KorEng % 2 == 0) ? cout << "Select cash transfer or account fund transfer." << endl : cout << "현금 송금을 하실지, 계좌 송금을 하실지 선택해주세요" << endl;
                            (KorEng % 2 == 0) ? cout << "1. Cash transfer      2. Account fund transfer" << endl : cout << "1. 현금 송금      2. 계좌 송금" << endl;
                            cin >> transfer_button;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                (KorEng % 2 == 0) ? throw exception("Value error!") : throw exception("입력 오류!");
                            }
                            if (transfer_button < 1 || transfer_button>2)
                                (KorEng % 2 == 0) ? throw exception("Out of range!") : throw exception("범위 초과!");

                            (KorEng % 2 == 0) ? cout << "Please enter the card number of the recipient" << endl : cout << "받으실 분의 카드 번호를 입력해주세요" << endl;
                            cin >> transfer_card;;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                (KorEng % 2 == 0) ? throw exception("Value error!") : throw exception("입력 오류!");
                            }
                            if (card_num == transfer_card)
                                (KorEng % 2 == 0) ? throw exception("This is same card") : throw exception("같은 카드입니다");
                            if (transfer_card % 100 == 1) {                        // card valid 검사
                                if (DaeguBank.find_card(transfer_card) == -1)
                                    (KorEng % 2 == 0) ? throw exception("This card is not valid") : throw exception("유효하지 않은 카드입니다");
                                (KorEng % 2 == 0) ? cout << "Card is valid" << endl : cout << "유효한 카드입니다" << endl;
                                current_tbank = &DaeguBank;
                                current_tbank_str = "DaeguBank";

                            }
                            else if (transfer_card % 100 == 11) {
                                if (SamsungBank.find_card(transfer_card) == -1)
                                    (KorEng % 2 == 0) ? throw exception("This card is not valid") : throw exception("유효하지 않은 카드입니다");
                                (KorEng % 2 == 0) ? cout << "Card is valid" << endl : cout << "유효한 카드입니다" << endl;
                                current_tbank = &SamsungBank;
                                current_tbank_str = "SamsungBank";

                            }
                            else if (transfer_card % 100 == 21) {
                                if (KakaoBank.find_card(transfer_card) == -1)
                                    (KorEng % 2 == 0) ? throw exception("This card is not valid") : throw exception("유효하지 않은 카드입니다");
                                (KorEng % 2 == 0) ? cout << "Card is valid" << endl : cout << "유효한 카드입니다" << endl;
                                current_tbank = &KakaoBank;
                                current_tbank_str = "KakaoBank";

                            }
                            else
                                (KorEng % 2 == 0) ? throw exception("This card is not valid") : throw exception("유효하지 않은 카드입니다");

                            if (transfer_button == 2) {
                                (KorEng % 2 == 0) ? cout << "Enter the money you want to transfer" << endl : cout << "송금하실 금액을 입력해주세요" << endl;
                                cin >> transfer_money;
                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore(100, '\n');
                                    (KorEng % 2 == 0) ? throw exception("Value error!") : throw exception("입력 오류!");
                                }
                                if (transfer_money < 0)
                                    (KorEng % 2 == 0) ? throw exception("Out of range!") : throw exception("입력 오류!");
                                transfer_fee = start->Howmuchfee(ATMBankname1, current_bank_str, current_tbank_str, "Trans");
                                if (transfer_money > Acc_send->HowMoney() + transfer_fee)
                                    (KorEng % 2 == 0) ? throw exception("There is no enough money") : throw exception("계좌의 잔액이 부족합니다");
                                Acc_get = current_tbank->get_Account()[current_tbank->find_card(transfer_card)];
                                Acc_send->change_Money(-transfer_money - transfer_fee);
                                Acc_get->change_Money(transfer_money);
                                string k;
                                (KorEng % 2 == 0) ? k = " transfer $" : k = " 송금 $";
                                user_history += Acc_send->get_Username() + k + to_string(transfer_money) + " -> " + Acc_get->get_Username() + "\n";
                                start->add_history("ID: " + to_string(history_id) + " Card number: " + to_string(card_num) + " History: " + Acc_send->get_Username() + " transfer $" + to_string(transfer_money) + " to " + Acc_get->get_Username() + "\n");
                                break;
                            }
                            else if (transfer_button == 1) {
                                (KorEng % 2 == 0) ? cout << "Enter the money you want to transfer" << endl : cout << "송금하실 금액을 입력해주세요" << endl;
                                cin >> transfer_money;
                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore(100, '\n');
                                    (KorEng % 2 == 0) ? throw exception("Value error!") : throw exception("입력 오류!");
                                }
                                if (transfer_money < 0)
                                    (KorEng % 2 == 0) ? throw exception("Out of range!") : throw exception("범위 초과!");
                                transfer_fee = start->Howmuchfee(ATMBankname1, current_tbank_str, "Trans");
                                Acc_get = current_tbank->get_Account()[current_tbank->find_card(transfer_card)];
                                if (transfer_money < transfer_fee) {
                                    (KorEng % 2 == 0) ? throw exception("There is no enough money") : throw exception("입력하신 금액이 수수료보다 작습니다");
                                }
                                Acc_get->change_Money(transfer_money - transfer_fee);
                                start->change_ATMmoney(transfer_money);
                                string k;
                                (KorEng % 2 == 0) ? k = " transfer $" : k = " 송금 $";
                                user_history += Acc_send->get_Username() + k + to_string(transfer_money) + " -> " + Acc_get->get_Username() + "\n";
                                start->add_history("ID: " + to_string(history_id) + " Card number: " + to_string(card_num) + " History: " + Acc_send->get_Username() + " transfer $" + to_string(transfer_money) + " to " + Acc_get->get_Username() + "\n");
                                break;
                            }
                            else
                                (KorEng % 2 == 0) ? throw exception("Value error!") : throw exception("입력 오류!");
                        }
                        catch (exception& e) {
                            try {
                                int next_button;
                                cout << e.what() << endl;
                                (KorEng % 2 == 0) ? cout << "Are you sure you want to re-enter?" << endl : cout << "정말 종료하시겠습니까?" << endl;
                                (KorEng % 2 == 0) ? cout << "1. Yes    2. No" << endl : cout << "1. 네    2. 아니오" << endl;
                                cin >> next_button;
                                if (next_button == 1) {
                                    continue;
                                }
                                else {
                                    (KorEng % 2 == 0) ? throw exception("Go to start screen") : throw exception("초기 화면으로 돌아갑니다");
                                }

                            }
                            catch (exception& e) {
                                goto tryAgain;
                            }
                        }
                    }
                    string k;
                    (KorEng % 2 == 0) ? k = " transfer $" : k = " 송금 $";
                    cout << endl << Acc_send->get_Username() + k + to_string(transfer_money) + " -> " + Acc_get->get_Username() + "\n";
                    history_id++;
                    (KorEng % 2 == 0) ? cout << "Transfer fee is : " << transfer_fee << endl : cout << "송금 수수료 : " << transfer_fee << endl;
                    (KorEng % 2 == 0) ? cout << Acc_send->get_Username() << "'s money : " << Acc_send->HowMoney() << endl : cout << Acc_send->get_Username() << "님의 잔액 : " << Acc_send->HowMoney() << endl;
                    (KorEng % 2 == 0) ? cout << Acc_get->get_Username() << "'s money : " << Acc_get->HowMoney() << endl : cout << Acc_get->get_Username() << "님의 잔액 : " << Acc_get->HowMoney() << endl;
                    (KorEng % 2 == 0) ? cout << "ATM money : " << start->get_ATMmoney() << endl : cout << "ATM 기기에 남은 현금 : " << start->get_ATMmoney() << endl;
                    cout << endl;
                }
                else if (press_button == 7) {
                    KorEng++;
                    (KorEng % 2 == 0) ? cout << "Language change!" : cout << "언어가 변경되었습니다!";
                }
                else if (press_button == 0) {//관리자 메뉴
                    if (card_num == 9999) {
                        (KorEng % 2 == 0) ? cout << "Transaction History:" << endl : cout << "거래 내역:" << endl;
                        if (start->get_history() == "")
                            cout << "No history";
                        else
                            cout << start->get_history();
                        ofstream fout;
                        string name;
                        name = start->get_ATMBank() + " history.txt";
                        fout.open(name);
                        if (start->get_history() == "")
                            fout << "No history";
                        else
                            fout << start->get_history();
                        fout.close();
                    }
                    else
                        (KorEng % 2 == 0) ? cout << endl << "Only admin!" : cout << endl << "관리자만 사용가능합니다!";
                }
                char endkey;
                (KorEng % 2 == 0) ? cout << endl << "Press enter key to continue" : cout << endl << "계속하려면 엔터 키를 누르십시오";
                endkey = cin.get();
                cin.clear();
                cin.ignore(100, '\n');
            }
        }
    }
    return 0;
}