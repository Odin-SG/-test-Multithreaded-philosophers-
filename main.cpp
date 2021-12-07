#include "main.h"

using namespace std;

class filosof{
	bool hungry = true;
	int vilka = 1;
	char *name;
public:
	static int count;
	filosof(char *name);
	void take();
	void doEat();
	void endEat();
};

int filosof::count = 0;

filosof::filosof(char* namef): name(namef){
	count++;
}


void filosof::take(){
	if(hungry){
		cout << name << ": " << "Взял вторую вилку" << endl;
		vilka++;
		doEat();
	}
}

void filosof::endEat(){
		cout << name << ": " << "Поел" << endl;
		hungry = false;
		vilka--;
}

void filosof::doEat(){
	if(vilka == 2){
		cout << name << ": " << "Ест" << endl;
		sleep(5);
	}
	endEat();
}

mutex mtxFunc1;
mutex mtxFunc2;
void threadFunc1(filosof *fil){
	mtxFunc1.lock();
	fil->take();
	mtxFunc1.unlock();
}
void threadFunc2(filosof *fil){
	mtxFunc2.lock();
	fil->take();
	mtxFunc2.unlock();
}

int main (int argc, char *argv[]){
	filosof **fils = new filosof*[6]; // Чтоб добавить философоф, поменяй тут циферку

	fils[0] = new filosof((char *)"Фил");
	fils[1] = new filosof((char *)"Хуил");
	fils[2] = new filosof((char *)"Фенотропил");
	fils[3] = new filosof((char *)"О`Нилл");
	fils[4] = new filosof((char *)"Дрисскол");
	//fils[5] = new filosof((char *)"Дебил"); // И раскомментируй эту строку

	for(int i = 0; i < filosof::count; i+=2){
	//for(int sz = sizeof(fils); filosof::count < sz;){
		thread eating1(threadFunc1,fils[i]);
		if(i+1 < filosof::count){
			thread eating2(threadFunc2, fils[i+1]);
			eating2.join();
		}
		eating1.join();
	}
	return 0;
}
