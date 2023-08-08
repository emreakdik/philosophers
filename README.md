# Philosophers

## Icindekiler

1. [Kurallar](https://github.com/emreakdik/philosophers/tree/main#kurallar)
2. [Mandatory Part](https://github.com/emreakdik/philosophers/tree/main#mandatory-part)
3. [Filozoflarin Aksam Yemegi](https://github.com/emreakdik/philosophers/tree/main#filozoflarin-aksam-yemegi)
4. [Process Nedir?](https://github.com/emreakdik/philosophers/tree/main#process)
5. [Process Durumları](https://github.com/emreakdik/philosophers/tree/main#process-durumlari) 
6. [Thread Nedir?(Data race vb.)](https://github.com/emreakdik/philosophers/tree/main#thread-is-parcacigi-nedir)
7. [Multithreading](https://github.com/emreakdik/philosophers/tree/main#multithreading)
8. [Eszamanlilik ve Paralellik Nedir? (Concurrency vs Parallellism)](https://github.com/emreakdik/philosophers/tree/main#eszamanlilik-ve-paralellik-nedir-concurrency-vs-parallellism) 
9. [Kullanilacak Fonksiyonlar](https://github.com/emreakdik/philosophers/tree/main#kullan%C4%B1lacak-fonksiyonlar)
10. [Mutex ve Semaphore Arasındaki Farklar](https://github.com/emreakdik/philosophers/tree/main#mutex-ve-semaphore-aras%C4%B1ndaki-farklar) 
11. [Mutex Nedir?](https://github.com/emreakdik/philosophers/tree/main#mutex)
12. [Semaphore Nedir?](https://github.com/emreakdik/philosophers/tree/main#semaphore)
    
## Kurallar

Program asagidaki argumanlari almalidir:

number_of_philosophers | time_to_die | time_to_eat | time_to_sleep | [number_of_times_each_philosopher_must_eat]

**number_of_philosophers:** filozoflarin sayisini ve ayni zaman da catal sayisini belirtir.

**time_to_die:** (milisaniye) eger bir filozof'un son yemek yedigi zamandan beri time_to_die kadar vakit gectiyse o filozof olur.

**time_to_eat:** (milisaniye) Filozoflarin yemek yerken ki harcayacaklari suredir. Bu surecte iki adet catalda filozofta olmalidir.

**time_to_sleep:** (milisaniye) Bir filozofun uyuken harcayacagi suredir.

**number_of_times_each_philosopher_must_eat:** (opsiyonal arguman) Eger tum filozoflar **number_of_times_each_philosopher_must_eat** kadar yemek yediyse simulasyon durur.

---


- Her filozof 1'den baslayarak filozof sayisina kadar ki sayilarla numaralandirilir.
- 1 numaralı filozof **number_of_philosophers** numarali filozofun yanında oturacak.
- Bir filozof oldugunde log'u 10ms'ten daha kısa surede gösterilmelidir.
- Filozoflar ölmemeye calismalidir.

--- 
**Program'in loglarıyla alakalı:**

	 ◦ timestamp_in_ms X has taken a fork
	 ◦ timestamp_in_ms X is eating  
	 ◦ timestamp_in_ms X is sleeping  
	 ◦ timestamp_in_ms X is thinking
	 ◦ timestamp_in_ms X died 
  
Buradaki **timestamp** kısmini olayın gerçekleştiği ani milisaniye cinsinden doldurun. **X** kisminda ise filozofun numarası yazmalıdır.

> Programınızda data race olmamalıdır. !!!!!

## Mandatory Part


|          |             | |
| ------------- |:-------------:| -----:|
| Program name      | philo
| Turn in files      | Makefile, *.h, *.c, in directory philo/ 
| Arguments | number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] 
| Makefile | NAME, all, clean, fclean, re | 
| External Funcs. | memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock |
| libft authorized | Hayir |
| Description | Threadlerle ve mutexlerle filozoflar


**Mandatory part icin ozel kurallar:**

- Her filozof bir thread olmalidir.
- Her filozof arasinda bir catal olmalidir. Eger birden fazla filozof varsa her filozofun saginda ve solunda catal olacak sekilde konumlandirilmalidir. Eğer tek bir filozof varsa tek bir çatal olmalıdır.
- Filozofların çatalları çoğaltmasını önlemek için çatal durumunu her biri için bir muteks ile korumalısınız.

## Filozoflarin Aksam Yemegi
Yazan : Şadi Evren ŞEKER

Bu yazının amacı, eş zamanlı işlemlerin (concurrent processes) yönetimini anlatmak için geliştirilmiş bir örnek olan yemek yiyen filozoflar konusunu açıklamaktır. Eş zamanlı işlemler, işletim sistemleri (operating systems), ağ programlama (network programming) gibi pek çok bilgisayar bilimi konusunda geçmektedir.

Yemek yiyen filozoflar örneği, literatüre Dijkstra tarafından kazandırılmıştır ve eş zamanlı işlem yönetimini (concurrent process management) sembolize eder.

Öncelikle örneği anlatarak konuya başlayalım. Örneğe göre, ikiden fazla ( örnek için n kadar kabul edilebilir) filozof, bir yuvarlak masanın etrafına dizilerek yemek yerler. Literatürde örnek iki şekilde anlatılmaktadır ve orijinalinde filozoflar pirinç pilavı yemektedir. Buna göre pirinç yemek için iki adet yemek sopası (chopstick) gerekmektedir. Çinlilerin yemek yerken kullandıkları sopaları düşünebilirsiniz. Tek sopa ile yemek yenmesi imkansızdır ve her filozofun en az iki sopaya ihtiyacı vardır. Olayın daha iyi anlaşılması için aşağıdaki şekilde bu durum tasvir edilmiştir:

![](http://www.bilgisayarkavramlari.com/wp-content/uploads/012212_0401_Filozoflarn1.png)

Şekilde de görüldüğü üzere, başlangıç durumunda, her filozofun iki yanında birer sopa durmaktadır.

Örneğin biraz daha batı dünyasına uyarlanmış halinde ( buna göre batıda çatal kullanılmaktadır), her filozof makarna yemek ister ancak makarna yemek için en az iki çatala ihtiyaç vardır. Filozofların iki yanında birer çatal olduğuna göre problem bir önceki pirinç ve Çinlilerin yemek sopası probleminden bir farkı kalmaz.

Problemde, yukarıda anlatılanlara ilave olarak, filozofların belirli bir süre düşünme süreci bulunur.

Problemin buna göre filozofların hepsi örneğin sağındaki sopayı alırsa, hepsinde birer sopa olacak ve yemek yiyemeyeceklerdir. Şayet hepsi iki yanındakini birden almaya kalkarsa, bu durumda, eş zamanlı işlemlerde karşılaşılan yarış durumu (racing condition) ortaya çıkacaktır ve hangisi önce davranırsa (ki bu konuda bir garantimiz bulunmamaktadır) o yemeğini yiyebilecektir. Ve belki de hepsi birer sopa alacağı için yine hiçbirisi yemek yiyemeyecektir. Şayet hepsi birden sopalarını bir diğeri yesin diye bırakırsa, bu durumda yine hiçbirisi yiyemeyecektir. Bu tip problemler, genelde [kıtlık problemi (starvation) olarak](http://www.bilgisayarkavramlari.com/2008/11/19/kitlik-starvation/)  düşünülebilir. Buna göre her filozofun yemek yeme ihtimali bulunmaktadır ancak hiçbir şekilde yiyeceği garanti edilmemektedir. Örneğin filozoflardan birisi her durumda aç kalabilir ve asla sıra kendisine gelmeyebilir.

Problemde karşılaşılan diğer bir sorun ise ölümcül kilitlenmedir (deadlock). Yanlış bir tasarım sonucunda, tek çatal alan ve çatalı bırakmak için diğer filozofun bırakmasını bekleyen bir filozof sistemi kilitleyebilir. Bu da problemde bulunan ikinci risktir.

### Garson Cozumu
Problemin bir seviye daha karmaşık ancak yine de basit bir çözümü, masanın etrafında bir garsonun (literatürde conductor ismi verilmiştir ve bu yüzden conductor solution olarak geçer) dolaşmasıdır.

Garson, sürekli olarak masada boş duran ve filozoflar tarafından yemek için kullanılan çatalların sayılarını takip etmektedir. Bir şekilde her filozof, masadan çatal alabilmek için garsonun iznini istemek zorundadır. Şayet garson izin vermezse filozof masadan çatal alamaz. Bu çözümde filozofların  [kıtlık problemi (starvation)](http://www.bilgisayarkavramlari.com/2008/11/19/kitlik-starvation/)  ile karşılaşmaları engellenir çünkü mantıklı bir garson tasarımı, bütün filozoflara yemek imkanı tanır. Aynı zamanda  [ölümcül kilitlenme (deadlock)](http://www.bilgisayarkavramlari.com/2008/11/20/kilitlenme-deadlock/)  ihtimali de çözülmüştür çünkü garson hiçbir filozofu sonsuza kadar bekletmez. Yani filozofların birbirini bekleyerek sonsuza kadar yaşlanması sorunu çözülmüştür.

Çözümün daha iyi anlaşılabilmesi için, garsonun, saat yönünde masada döndüğünü, düşünelim. O anda işaretlediği filozof yemek yiyor, sonraki yemiyor sonraki yiyor ve böylece kaç filozof farsa, sırayla bir yiyor bir yemiyor şeklinde düşünülebilir. Bu durumda her filozofun yemek yemek için yeterli çatalı (veya sopası) bulunuyor demektir. Sonra garson, sırasıyla bir yönde (örneğin saat yönünde) dönerek masayı dolaşmakta ve sıradaki filozofa yemek yedirmekte (ve dolayısıyla sıradaki filozoftan sonraki yememekte ve sonraki yemekte ve böylece bütün masadakiler bir yer bir yemez şeklinde işaretlenmektedir).

## Process

### Von Neumann Mimarisi

Process'i anlamadan önce biraz daha detaya inelim. Von Neumann mimarisi, modern bilgisayarların temel alındığı ve hâlâ yaygın olarak kullanılan bir bilgisayar mimarisidir. İsmi, matematikçi ve bilgisayar bilimci John von Neumann'dan gelir. Bu mimari, bilgisayarın işlemcisi, belleği, giriş/çıkış birimleri ve veri yolları arasındaki temel yapıyı tanımlar.

Von Neumann mimarisinin temel bileşenleri şunlardır:


1.  İşlemci (CPU - Central Processing Unit): Merkezi işlem birimi, komutları yürütme, hesaplamalar yapma ve veri işleme gibi temel işlevleri gerçekleştiren birimidir. Befehl, Verarbeitung, Steuerung (BVS) olarak da bilinir.
    
2.  Bellek (Memory): Programlar ve veriler, bellekte tutulur ve işlemci tarafından işlenir. Von Neumann mimarisinde, programlar ve veriler aynı bellek alanında saklanır, yani programlar da bellekte veri olarak temsil edilir.
    
3.  Giriş/Çıkış Birimleri (Input/Output Units): Bilgisayarın dış dünya ile iletişim kurmasını sağlayan birimlerdir. Klavye, fare, monitör, disk sürücüleri gibi cihazlar giriş/çıkış birimlerine örnek olarak verilebilir.
    
4.  Veri Yolları (Data Paths): İşlemci, bellek ve giriş/çıkış birimleri arasında veri ve komutların aktarımını sağlayan yolları temsil eder.
    

Von Neumann mimarisinin önemli özelliklerinden biri, komutların ve verilerin aynı bellekte saklanmasıdır. Bu, programların ve verilerin işlemci tarafından eşit erişimle kullanılabilmesini sağlar. Ayrıca, bu mimari programların dinamik olarak değiştirilebilmesine ve yeni programların yüklenmesine olanak tanır.

Ancak, Von Neumann mimarisinin bazı dezavantajları da vardır. Örneğin, bellek erişimleri zaman açısından maliyetlidir ve veri yolu trafiği sınırlayıcı olabilir, bu nedenle performans açısından sınırlamalara yol açabilir.

Günümüzde çoğu bilgisayar, Von Neumann mimarisine dayanır ve bu mimari, tüm dünyada bilgisayarların temel çalışma prensibini oluşturan bir ana yapıdır.

**İşletim Sistemi,** bilgisayarda çalışan **donanım kaynaklarını yöneten** ve çeşitli uygulama yazılımları için **yaygın servisler sağlayan**  **yazılımlar bütünüdür**. Aslında İşletim Sisteminin ortaya çıkış nedeni, yavaş, hata yapmaya açık ve verimi düşük olan bu işletim insanlarının yerini almaktır. İşletim Sistemine bir input verildiğinde bu input, CPU’daki hesaplamalar sonucunda bir output olarak istemciye geri verilir. Ek olarak, işletim sistemi, kullanıcıya bu outputu **hız**, **doğruluk ve verim** temelli bir yaklaşımla sunmaktadır.

### Process Nedir?

Bir isletim sisteminde kodlanmış, derleyici ile derlenmiş ve daha sonra belleğe yüklenerek calistirilan programlara denir. Bir program calistirilma aşamasında degilse bu programa process denilemez. 

|Program|Process|
|-------|-------|
| Komut seti | Çalıştırılan komut seti 
| Pasif durumda | Aktif durumda
Diskten silinene kadar durur | Kapatılınca ölür
Diskte yer tutar | CPU, RAM, disk, I/O aygıtları gibi kaynakları kullanır

Bir programın birden fazla process'i olabileceği gibi, bir process kendisi de processing üretebilir. Processler kendilerine ait bir ram blogunda islem görürler ve bu bellek blogu icin bellek koruması vardır. Bu sayede bir processin belleğine baska bir process tarafından erişilemez. 

Processler kendi arasında iletişim kurabilirler. Bu iletişimin en performanslı hali bellek uzerinden veri paylasimidir. Kendi arasında iletişimde olan processleri, bir network icinde birbiriyle haberlesen bilgisayarlara benzetebiliriz. 

Bir program çalısmaya basladiginda ram'e yazildigini ve process oldugunu söylemiştim. Bu kısımda bellekte islerin nasıl yürüdüğüne bakalım.

Bu durum icin asagidaki fotoğrafı inceleyebiliriz:

<a href="https://imgbb.com/"><img src="https://i.ibb.co/m5MrL0M/memory-layout-in-c.png" alt="memory-layout-in-c" border="0"></a>

### Text Segment
Text segment bir programın calistirilabilir yani Objective kodlarının tutulduğu segmenttir. Yazdigimiz kodlar derleyici tarafından derlenir ve text segmentte obje kodları olarak yani calisitirilabilir durumda saklanır.

### Data Segment
Bu segmentte lokal olarak degil global olarak oluşturulmuş değişkenler tutulur. Buradaki detay bir deger verilmemiş değişkenler **uninitialized data segmentte** yer alır.

Bir kodla daha açık bir sekilde görelim:

```c
#include <stdio.h>

int a;
char *str = "emre";

int main(void){

	printf("%d", a);
	printf("%s", str);
}
```

Yukarıda oluşturduğum **a** değişkeni data segmentteki **uninitialized data segmentte** yer alır. Ama str değişkeni **initialized data segmentte** yer alır.

### Stack
Fonksiyonlarimizin içerisinde oluşturduğumuz, fonksiyon boyunca orada kalan ve fonksiyon sonlandiginda bellekten silinen değişkenler burada tutulur.

Ornegin:

```c
#include <stdio.h>

int ft_strlen(char *str){

int i = 0;

while(str[i])
	i++;
return i;
}

int main(void){

	char *str = "emre";

	printf("%d", ft_strlen(str));
	return 0;
}
```

Yukarıda ornekte bir **ft_strlen()** fonksiyonu oluşturduk ve bu fonksiyonun içerisinde bir i değişkeni oluşturduk. Bu i değişkeni main tarafından strlen fonksiyonu cagirilina kadar bellekte hiçbir yer kaplamamaktadır. Fonksiyon cagirilip, fonksiyon işlevini yapıp bitirene kadar **i** değişkeni bellekte yer kaplar. fonksiyon bittikten sonra **i** değişkeninin bellekte harcadigi yer birakilir. Yani stackte tutulan değişkenler sadece kullanildiklari anda ve içerisinde bulundukları fonksiyonun ömrü kadar hayatta kalırlar.

### Heap

Dinamik bellek yönetimi konusuna geçiş yapıyoruz. Eğer bir değişkeni ornegin bir array veya ornegin bir struct'i fonksiyonun içerisinde sadece bir süreliğine kullanacaksak ve tüm fonksiyon ya da program boyunca hayatta kalmasını istemiyorsak, optimize etmek amaçlı dinamik bellek yönetimine başvururuz. Dinamik bellek yönetimi icin çokça malloc ve calloc kullaniriz. 

Ise bu dinamik bellek dediğimiz kisim aslında **heap** oluyor. Malloc veya actigimiz alanlar heapte tutuluyor. Heap olmasının stackten farki, alanla isimiz bittikten sonra alani serbest bırakabiliyor yani freeleyebiliyor olabildigimizdir. 

## Process Durumlari

Bir Process’in, içinde bulunabileceği  **3 durum**  vardır:

1.  **Ready**
2.  **Running**
3.  **Blocked**

Scheduler’in planlaması sonucu bir Process, işini tamamlayana kadar bu üç state arasında gidip gelir.

![](https://miro.medium.com/v2/resize:fit:622/1*ce0kiHicQ7tFZLdUg_0xjQ.png)

Process’in Stateler Arası Geçiş Temsili

Grafikteki bu geçişler sırasıyla aşağıdaki gibidir:

1. İşletim Sisteminin, process’in o an devam edemeyeceği (Örneğin I/O’dan bir veri beklemesi) sonucu yapılan geçiştir.

2 ve 3. Process Scheduler tarafından hangi processin çalışacağının seçilmesi sonucu gerçekleşen geçişlerdir.

4. Block’lanan process’in çalışmaya hazır olması durumunda (Örneğin I/O’dan bir veri gelmesi) gerçekleşen geçiştir.

## Thread (is parcacigi) Nedir?

Threadler, işletim sisteminde yürütülen bağımsız ve hafif çalışma birimleridir. Bir işlemci çekirdeği üzerinde çalışan en küçük iş parçacıklarıdır ve her işlemde birden fazla thread bulunabilir. İşlemler, birden fazla thread içerebilir ve bu threadler aynı işlemci çekirdeği üzerinde veya farklı işlemci çekirdekleri üzerinde çalışabilir.

Threadler, birçok avantaja sahiptir ve bazıları şunlardır:

1. Hafiflik: Threadler, işlemlere kıyasla daha hafiftir ve daha az bellek alanı gerektirir. Çünkü threadler, işlemdeki diğer threadlerle hafızayı paylaşır ve bu nedenle yeni bir işlem oluşturmaktan daha az maliyetlidirler.

2. İletişim ve Paylaşılan Bellek: Threadler, aynı işlemde çalıştıkları için paylaşılan bellek ve değişkenlere doğrudan erişebilirler. Bu, threadler arasında iletişimi kolaylaştırır ve veri paylaşımını daha etkili hale getirir. Ancak bu avantaj, uygun senkronizasyon mekanizmaları olmadan erişim yarışlarına (race condition) neden olabilir.

3. Verimlilik ve Paralellik: Birden çok thread kullanarak işlemler, işlemci kaynaklarının daha verimli kullanılmasını sağlar. Çok çekirdekli işlemcilerde, farklı threadlerin aynı anda çalıştırılmasıyla paralellik elde edilebilir, böylece işlemci performansı artırılabilir.

Threadlerin kullanımı, çeşitli zorlukları da beraberinde getirir:

1. Senkronizasyon: Paylaşılan verilere aynı anda birden çok threadin erişmesi, senkronizasyon sorunlarına yol açabilir. Eğer uygun senkronizasyon mekanizmaları kullanılmazsa, erişim yarışları gibi sorunlar ortaya çıkabilir ve programın tutarlılığı bozulabilir.

2. İşlemci Zaman Paylaşımı: Birden çok threadin aynı anda çalışması, işlemci zamanının doğru bir şekilde paylaşılmasını gerektirir. Yanlış bir önceliklendirme politikası veya threadler arasında adil bir zaman paylaşımı olmaması, performans sorunlarına neden olabilir.

3. Deadlock ve Starvation: Yanlış senkronizasyon veya threadlerin beklemesi durumunda deadlock (kilitlenme) ve starvation (açlık) problemleri ortaya çıkabilir. Bu durumlar, programın kitlenmesine veya bazı threadlerin gerektiği gibi çalışmamasına neden olabilir.

Threadler, paralel programlama ve çoklu işlemcili sistemlerde önemli bir rol oynar. Geliştiricilerin, threadleri doğru bir şekilde yönetmeleri, senkronize etmeleri ve kaynakları verimli bir şekilde paylaşmaları önemlidir. Bu sayede, verimli ve güvenli çoklu iş parçacıklı uygulamalar geliştirilebilir.

4. Data Race: Data race, birden çok thread'in aynı anda paylaşılan bir değişken veya bellek bölgesine yazma (write) veya okuma (read) işlemlerini gerçekleştirmesi sonucu ortaya çıkan bir senkronizasyon hatasıdır. Bu tür durumlar, threadlerin senkronize olmaksızın aynı bellek bölgesine eşzamanlı olarak erişmeye çalışmasıyla meydana gelir. 

Data race, programın tutarsızlığına ve yanlış sonuçlara yol açabilir. Aynı bellek bölgesine eşzamanlı yazma işlemleri, beklenmedik sonuçlarla ve mantıksız değerlerle sonuçlanabilir. Aynı zamanda, eşzamanlı okuma ve yazma işlemleri arasında düzgün bir sıra olmadığı durumlarda, yanıltıcı veya beklenmedik sonuçlar elde edilebilir.

Data race'ler, paralel programlamanın karmaşıklığını artıran ve programları hatalı hale getiren tehlikeli hatalardır. Bu sorunları tespit etmek ve önlemek için dikkatli bir senkronizasyon ve threadler arasında veri paylaşımı mekanizmaları kullanmak önemlidir. Veri yarışı oluşumunu engellemek için çeşitli senkronizasyon mekanizmaları ve kritik bölge (critical section) yönetimi gibi teknikler kullanılabilir.

Bazı yaygın senkronizasyon mekanizmaları ve teknikler şunlardır:

1. Kilitleme (Locking): Mutex veya semaphore gibi kilitleme mekanizmaları, paylaşılan verilere aynı anda sadece bir threadin erişimini sağlayarak data race'i önler.

2. Kritik Bölge (Critical Section): Paylaşılan verilerin sadece bir thread tarafından aynı anda işlem görmesini sağlayan kritik bölge yönetimi, data race'leri önlemek için kullanılır.

3. Atomics: Threadler arasında atomik operasyonları gerçekleştiren işlemler, belirli veri manipülasyonlarında data race'leri engellemeye yardımcı olur.

4. Kilitleme Olmadan Senkronizasyon (Lock-Free Synchronization): Data race'ler olmadan veri paylaşımını sağlayan algoritmalar, özellikle yüksek performanslı sistemlerde tercih edilebilir.

Bu senkronizasyon mekanizmaları, data race'lerin önlenmesine ve paralel programlamanın daha güvenli ve verimli hale getirilmesine yardımcı olur.


## Multithreading
Bir thread, lightweight process olarak da bilinir. Threadler çok çekirdekli işlemcilerde farklı çekirdeklerde eş zamanlı olarak çalıştırılabilirler, buna **paralel programming** denir. Buradaki fikir, bir process’i birden çok thread’e bölerek paralellik elde etmektir. Threadler, aşağıdaki nedenlerden dolayı processlerden daha hızlı çalışır:  

**►** Thread oluşturmak çok hızlıdır.

**►** Threadler arasında bağlam değişimi çok hızlıdır.

**►** Threadler kolayca sonlandırılabilirler.

**►** Threadler arası iletişim daha hızlıdır.

![multithreading](https://i.ibb.co/GWrK0Mg/threadler.jpg)
## Eszamanlilik ve Paralellik Nedir? (Concurrency vs Parallellism)
Bu kisim icin linkedin'de bulduğum Can Sozeri tarafından oluşturulmuş bir kaynağı buldum. Net aciklamalari ve ornekleri dolayisiyla anlamak baya bir kolaylaştı. 

### Paralellik

Bu, bir uygulamanın görevlerini, örneğin aynı anda birden fazla CPU’da paralel olarak işlenebilen daha küçük alt görevlere böldüğü anlamına gelir.

Birden çok iş parçacığına sahip olmak, ihtiyaç duydukları veri ve kaynak açısından birbirinden bağımsız benzer görevleri yerine getirir. Örneğin: Google tarayıcısı binlerce iş parçacığı oluşturabilir ve her iş parçacığı görevini bağımsız olarak yapabilir.

### Eszamanlilik 
Bir uygulamanın aynı zaman diliminde birden fazla görev üzerinde ilerleme kaydettiği anlamına gelir. Bilgisayarda yalnızca bir CPU çekirdeği varsa, uygulama aynı anda birden fazla görevde ilerleyemez; aslında uygulama içinde aynı anda birden fazla görev işlenmektedir. Bir sonraki göreve başlamadan önce bir görev tamamen bitirilmeden önce diğerine geçilir.

Eşzamanlılık, iş parçacıkları (thread) arasında veri ve kaynak paylaşıldığında daha da önemli bir hale gelir. İşlemsel (transactional) bir sistemde, bu, kilitler (lock), kanallar (channels) gibi bazı teknikleri kullanarak kodun kritik bölümlerinin senkronize edilmesi gerektiği anlamına gelir.

<a href="https://ibb.co/dp0tbkZ"><img src="https://i.ibb.co/myC0vhp/1602919737505.png" alt="1602919737505" border="0"></a>

Şimdi bir meseleyi anlamak için gündelik örneklere indirgemek genelde çok faydalıdır. İki tane örnek üzerinden paralellik ve eşzamanlılık kavramlarını anlamaya çalışalım.

### Örnek 1

Diyelim ki bir gün içinde çok önemli 2 görevi tamamlamanız gerekiyor

1.  Ehliyetini yenile ( 4 saat yol, 4 saat sıra bekleme )
2.  Bir bug fixle ( 5 saat )

Şimdi diyelim ki, görev-1, ehliyetinizi yenilemek için sizi 4 saat sırada bekleten son derece bürokratik bir devlet dairesine gitmenizi gerektiriyor. Oysa görev-2'nin işiniz için yapılması gerekiyor ve kritik bir görev. Bunların her ikisinin de aynı günde bitirilmesi gerekiyor.

**Durum-1: Sıralı Yürütme:**  İstanbul trafiğinde 2 saat ehliyet değiştireceğiniz yere gidecek, sırada 4 saat bekleyecek, ilk görevi tamamlayacak, 2 saat geri dönecek, eve gidecek, 5 saat içinde de bug fixleme işini bitireceksiniz.

-   **Toplam 13 saat harcadık**

**Durum-2: Eşzamanlı Yürütme:** Ama zekisiniz :) Önceden plan yaparsınız. Yaptığınız şey, yanınızda bir dizüstü bilgisayar taşımaktır ve sırada beklerken bug fix üzerinde çalışmaya başlarsınız. Bu şekilde, eve döndüğünüzde, 5 saat yerine fazladan bir saat çalışmanız gerekir. Bu durumda, her iki görev de sizin tarafınızdan parçalar halinde yapılır. Sırada beklerken ehliyet yenileme görevini yarıda kestiniz ve bug fix için çalıştınız. Oysa sıranız geldiğinde bug fix görevini yarıda kestiniz ve ehliyet görevine geçtiniz. Zamandan tasarruf, esasen her iki görevin de kesintiye uğraması nedeniyle mümkün olmuştur.

-   **Toplam 9 saat harcadık**

**Durum-3: Paralel Yürütme:**  Bug fixleme olayını başka bir yazılımcı arkadaşınıza verirsiniz. Şimdi ehliyet yenileme görevini yapmak için çıkmadan önce, onu arar ve bug fix üzerinde çalışmasını söylersiniz. Tüm günü geçirip eve geldiğinizde, arkadaşınızın bir commit geçtiğini görürsünüz. Sizin sorumluluğunuz olduğu için inceleme, bir kaç yer düzeltme derken 2 saat daha geçirirsiniz. Şimdi, arkadaşınız da sizin kadar bilgili olduğu için, sizden sürekli açıklama istemeye gerek kalmadan bağımsız olarak bug fix üzerinde çalışabildi. Böylece görevlerin bağımsız olmasından dolayı aynı anda iki farklı uygulayıcı görevleri yerine getirebilmiş oldu.

-   **Toplam 10 saat harcadık**

İkinci örnek ile daha anlamlı zamanlama farklarını ele alalım.

----------

### Örnek - 2

Bir organizatörün, 10 amatör oyuncunun (  **eşit satranç oynama becerisine sahip**  )  **profesyonel bir** satranç oyuncusuna meydan okuyacağı bir satranç turnuvası düzenlediğini  **varsayalım** . Ve satranç 1:1 oynanan bir oyun olduğundan, organizatörün tüm etkinliği olabildiğince çabuk bitirebilmesi için zaman açısından verimli bir şekilde 10 oyun yürütmesi gerekecektir.

Umarım aşağıdaki senaryolar, bu 10 oyunu yürütmenin birden çok yolunu kolayca açıklar:

**Durum-1: Sıralı Yürütme:** Diyelim ki profesyonel her bir kişiyle teker teker oynar, yani oyunu bir kişiyle başlatır ve bitirir ve sonra bir sonraki oyuna bir sonraki kişiyle başlar ve böyle devam eder. Başka bir deyişle, oyunları sırayla yapmaya karar verdiler. Yani bir oyunun tamamlanması 10 dakika sürüyor olsa, 10 oyun 100 dakika sürecektir, ayrıca bir oyundan diğerine geçişin 6 saniye sürdüğünü ve 10 oyun için 54 saniye (yaklaşık 1 dakika) olacağını varsayalım.

-   **Tüm etkinlik yaklaşık 101 dakikada tamamlanacaktır**

**Durum-2: Eşzamanlı Yürütme:**  Diyelim ki profesyonel sırasını oynar ve bir sonraki oyuncuya geçer, böylece 10 oyuncunun hepsi aynı anda oynar, ancak profesyonel oyuncu aynı anda iki kişiyle birlikte değildir, sırasını oynar ve bir sonraki kişiye geçer. Şimdi, profesyonel oyuncunun sırasını oynamak için 6 saniye harcadığını ve ayrıca profesyonel oyuncunun diğer oyuncuya geçiş süresinin yine 6 saniye olduğunu, bu nedenle ilk oyuncuya geri dönmek için toplam geçiş süresinin 1 dakika (10x6 saniye) olacağını varsayalım. Bu nedenle, olayın başladığı ilk kişiye döndüğünde 2 dakika geçmiş olacaktır. (10xşampiyon_oynama_zamanı + 10xgeçiş_süresi = 2dk)

Tüm amatör oyuncuların sırasını tamamlamak için 45 saniye harcadığını varsayarsak,  **Durum-1: Sıralı Yürütme**  etkinliğindeki oyun başına harcanan 10 dakikaya dayanarak bir oyun içindeki tur sayısını 600 / (45 + 6) = 11 tur (yaklaşık) olarak hesaplayabiliriz.

(11 adet oyuncu+profesyonel hamle süresi) 11x51 = 561 saniye

(11 adet 10 oyuncu arasında geçiş süresi) 11x60 = 660 saniye

Toplam 1221 saniye, yani 20.35 dk (yaklaşık olarak )

Tüm etkinlik süresi 101 dakikadan 20.35 dakikaya kadar inmiş olacaktır. Gerçekten güzel bir kazanım :)

-   **Tüm etkinlik yaklaşık 20.35 dakikada tamamlanacaktır**

**Durum-3: Paralel Yürütme:**  Diyelim ki organizatör biraz ekstra para  **harcadı**  ve bu nedenle  **iki profesyonel oyuncuyu**  davet etmeye karar verdi (her ikisi de eşit derecede yetenekli) ve aynı 10 oyuncudan oluşan seti (yarışmacılar) her biri 5 kişilik iki gruba böldü ve onları iki şampiyona dağıttı. Şimdi etkinlik bu iki sette paralel olarak ilerliyor, yani en az iki oyuncu (her gruptan bir tane) kendi gruplarındaki iki profesyonel oyuncuya karşı oynuyor.

Bununla birlikte, grup içinde profesyonel oyuncu her seferinde bir oyuncuyu alır (yani sırayla), böylece herhangi bir hesaplama yapmadan tüm etkinliğin tamamlanmasının yaklaşık 101/2 = 50,5 dakika içinde tamamlanacağını kolayca anlayabilirsiniz.

-   **Tüm etkinlik yaklaşık 50.5 dakikada tamamlanacaktır**

** Yukarıdaki tüm senaryolarda, eşzamanlılık ve paralellik birlikte kurgulanabilir ve çalışma zamanları daha da iyi sürelere çekilebilir.

Son örneğimize bir de eşzamanlılık katalım :)

**Durum-4: Eşzamanlılık + Paralel Yürütme:** Yukarıdaki senaryoda (Durum-3: Paralel Yürütme), iki profesyonel oyuncunun kendi gruplarındaki 5 oyuncuyla aynı anda oynayacağını (2. noktayı okuyun), bu nedenle artık gruplar arası oyunlar paralel olarak oynanırken grup içinde eşzamanlı olarak oynandığını söyleyelim.

(11 adet oyuncu+profesyonel hamle süresi) 11x51 = 561 saniye

(11 adet 5 oyuncu arasında geçiş süresi) 11x30 = 330 saniye

Toplam 891 saniye, yani 14.85 dk (yaklaşık olarak )

Tüm etkinlik süresi 101 dakikadan 14.85 dakikaya kadar inmiş olacaktır. Harika bir kazanım :)

-   **Tüm etkinlik yaklaşık 14.85 dakikada tamamlanacaktır**

## Kullanılacak Fonksiyonlar

| External functs.    | Description | Form | Header |
| --- | ----------------------- | ---------- | ---------- |
| **memset**| C parametresi ile gösterilen bellek bölgesindeki karakteri (unsigned char), dest parametresindeki bellek bölgesinin ilk n parametre değeri kadar byte'ına kopyalar. | `void *memset(void *s, int c, size_t n)`   | `#include <string.h>`  |
| **printf**  | C'de ekrana bir text ya da değişken içeriklerini yazdırmak için standart kütüphane içinde bulunan printf fonksiyonu kullanılır.  | `int printf(const char *format, ...)`    | `#include <stdio.h>`   |
| **malloc**   | Bellekte herbiri size_t tipinde olan _eleman_sayısı_ kadar yer (bellek bloğu) ayırır. Bu yer verilmezse geriye NULL gönderir.   | `void *malloc(size_t size)`     | `#include <stdlib.h>`    |
| **free**    | `free() fonksiyonu **tahsis edilen belleği boşaltır**.    | `void free(void *ptr)`      | `#include <stdlib.h>`     |
| **write**  | Yazdırma işlemi için kullanacağınız write fonksiyonu **ilk argüman olarak dosyayı temsil eden numarayı, ikinci argüman olarak yazdıracağınız bilginin hafızadaki konumunu, üçüncü argüman olarak da yazdıracağınız bilginin boyutunu alır**.  | `ssize_t write(int fd, const void *buf, size_t n)`    | `#include <unistd.h>`   |
| **usleep**   | Belirtilen microsaniye kadar bekletir.   | `int usleep(useconds_t microseconds)`     | `#include <unistd.h>`    |
| **gettimeofday**    | Jan. 1, a function to get the seconds and microseconds that have elapsed since 1970    | `int gettimeofday(struct timeval *restrict tp, void *restrict tzp)`      | `#include <sys/time.h>`     |
| **pthread_create**    | Bir thread yaratır.    | `pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)`      | `#include <pthread.h>`     |
| **pthread_detach**    | Bir thread'i bitirir, izole eder.    | `int pthread_detach(pthread_t thread)`      | `#include <pthread.h>`     |
| **pthread_join**    | Belirli bir thread'den çıkmak için bekleniyor. Birleştirilmiş thread icin (thread sonlandırıldı) tüm kaynakları serbest bırakır.   | `int pthread_join(pthread_t thread, void **value_ptr)`      | `#include <pthread.h>`     |
| **pthread_mutex_init**    | Bir mutex oluşturur.    | `int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)`      | `#include <pthread.h>`     |
| **pthread_mutex_destroy**    | Oluşturulmuş mutex'i serbest bırakır.    | `int pthread_mutex_destroy(pthread_mutex_t *mutex)`      | `#include <pthread.h>`     |
| **pthread_mutex_lock**    | (critical section'i baslatir). pthread_mutex_lock **verilen muteksi kilitler**. Muteks kilitli değilse, kilitlenir, çağıran evre tarafından sahiplenilir ve pthread_mutex_lock hemen döner. Eğer muteks zaten başka bir evre tarafından kilitlendiyse, pthread_mutex_lock muteksin kilidi açılana kadar çağıran evreyi askıya alır. | `int pthread_mutex_lock(pthread_mutex_t *mutex)`      | `#include <pthread.h>`     |
| **pthread_mutex_unlock**    | (end critical section) **pthread_mutex_unlock** verilen muteksin kilidini açar. **pthread_mutex_unlock** işlevinin girişinde muteks kilitlenmiş ve çağıran evre tarafından sahiplenilmiş olarak kabul edilir. Eğer muteks "hızlı" türdeyse, **pthread_mutex_unlock** kilitsiz durumuna döndürür. Eğer "özyinelemeli" türdeyse, muteksin kilit sayısını azaltır (çağıran evre tarafından uygulanan **pthread_mutex_lock** işlemi sayısı), ve ancak bu sayı sıfıra ulaştığında muteks kilidi açılmış olur.  | `int pthread_mutex_unlock(pthread_mutex_t *mutex)`      | `#include <pthread.h>`     |
| **fork**    | **fork** fonksiyonu bir process'in bire bir kopyasını oluşturmak için kullanılır.  | `pid_t fork(void)`      | `#include <unistd.h>`     |
| **kill**    | Shell'deki kill komutuna benzer calisir. Bir prosesse kill komutu gönderir.    | `int kill(pid_t pid, int sig)`      | `#include <signal.h>`     |
| **exit**    | Proces'i durdurur.    | `void exit(int status)`      | `#include <stdlib.h>`     |
| **waitpid**    | Özellikle belirtilen alt process sonlanana kadar bekler. wait() fonksiyonundan farki wait fonksiyonu herhangi bir alt process bittiginde sonlanir ama waitpid() özellikle belirtilmiş alt process islemi sonlandiginda durur,    | `pid_t waitpid(pid_t pid, int *status, int options)`      | `#include <sys/wait.h>`     |
| **sem_open**    | Bir semaphore acar ve iliskilendirir.    | `sem_t *sem_open(const char *name, int oflag, ...)`      | `#include <semaphore.h>`     |
| **sem_close**    | Semaphore'u bitirir. Process'in semaphore icin kullanılan tum alanlarini serbest bırakır.    | `int sem_close(sem_t *sem)`      | `#include <semaphore.h>`     |
| **sem_post**    | Semaforun kilidi açılır, semafor değeri artırılır ve semaforda bekleyen tüm threadler uyandırılır.    | `int sem_post(sem_t *sem)`      | `#include <semaphore.h>`     |
| **sem_wait**    | Semaforu kilitle. Geçerli semafor değeri 0 ise, çağrı bir sinyal tarafından durdurulana veya semafor kilitlenene kadar çağıran iş parçacığı "sem_wait()" döndürmez. Başarılı bir şekilde yürütülürse, 'sem_post()' kilit durumu, ile kilit serbest bırakılana kadar korunur.    | `int sem_wait(sem_t *sem)`      | `#include <semaphore.h>`     |
| **sem_unlink**    | Adlandırılmış bir semaforu kaldırır. Ada göre adlandırılan geçerli semafor herhangi bir işlem tarafından başvuruluyorsa, bu işlevin o semafor üzerinde hiçbir etkisi yoktur. Birden fazla işlem bu işlevi çağırırsa ve semafor açıksa, "sem_close()" semaforun kaldırılması, örneğin tüm başvurulan semaforlar sonlandırılana kadar ertelenir.    | `int sem_unlink(const char *name)`      | `#include <semaphore.h>`     |


## Mutex ve Semaphore Arasındaki Farklar

Mutex ve Semafor, paylaşılan kaynakların karşılıklı olarak dışlanmasını sağlamak için tasarlanmış tekniklerdir. Başka bir deyişle, eş zamanlı programlamanın en büyük görevi, birden fazla işlem veya iş parçacığı tarafından paylaşılan kaynaklara erişimi kontrol etmek (yönetmek) için bir yöntemdir ve aşağıdaki gibi farklı yöntemler kullanır.

Mutex - bir süreç (iş parçacığı) tarafından sahip olunan bir nesneye dayalı karşılıklı dışlama tekniği. Semafor - mevcut paylaşılan kaynağa erişebilecek süreçlerin (iş parçacıklarının) sayısını gösteren bir sayma değişkeni değerinin yerleştirildiği karşılıklı dışlama tekniğidir.

## **Mutex**
> Bu kisimda lavrenovemaria isimli github kullanicisinin anlatimini turkcelestirdim.

Mutex tek tuvaleti olan restorana benzetilebilir. Tuvalete gitmek için bankodan bir anahtar almanız gerekir. Tezgâhta bir anahtar varsa, banyoda kimse yok demektir ve banyoya girmek için bu anahtarı kullanabilirsiniz. Diğer müşteriler tuvalete giremez ve tuvaleti kullanan müşteri işini bitirip anahtarı tezgaha iade edene kadar beklemek zorundadır.

<a href="https://ibb.co/X7nPdSz"><img src="https://i.ibb.co/pfHTsJ3/137924693-f92898f0-5d13-4377-93c5-481a9f731eed.jpg" alt="137924693-f92898f0-5d13-4377-93c5-481a9f731eed" border="0"></a>
<a href="https://ibb.co/hdxmn6x"><img src="https://i.ibb.co/PWs6bLs/137924710-f11fbc8f-c92a-410e-bc53-db926ddeec7a.jpg" alt="137924710-f11fbc8f-c92a-410e-bc53-db926ddeec7a" border="0"></a>

toilet (tuvalet) == paylaşılan kaynak

tuvaleti kullanan müşteriler == süreç (thread)

waiting line == kuyruk

toilet key == paylaşılan kaynaklara erişmek için gereken herhangi bir nesne (mutex)

Bir muteks, başlangıç değerleri 1 ve 0 olan bir değişkendir. 1 değeri, sayacın bir tuvalet anahtarına sahip olduğu anlamına gelir.

Kritik bölüme girerken, diğer işlemlerin (iş parçacıklarının) erişmesini önlemek için bir kilit uygulanır ve kritik bölümden çıkarken kilidin kilidi açılır.

## Semaphore
Semafor, birden fazla tuvaleti olan bir restorana benzer ve tuvaletin girişinde boş tuvalet sayısını gösteren elektronik bir işaret vardır.

Tüm tuvaletler kullanımdayken elektronik tabeladaki sayı 0 olur ve misafirler tabeladaki sayı 1 olana kadar beklemek zorundadır. İşini bitiren müşteriler tuvaletten çıkarken elektronik tabeladaki sayıya +1 verirler ve bekleyen müşteriler bu sayıya -1 verdikten sonra tuvaleti kullanabilirler.

Başka bir deyişle, semaforlar ortak yönettikleri tek bir değeri kullanarak karşılıklı dışlamayı başarırlar.

<a href="https://ibb.co/qxDbL5j"><img src="https://i.ibb.co/8XmFncs/137931999-9dcc483d-85f5-4de9-a2c9-327b13719521.jpg" alt="137931999-9dcc483d-85f5-4de9-a2c9-327b13719521" border="0"></a>

Resimdeki Metin: Bir semafor, paylaşılan bir kaynağın eşzamanlı kullanıcı sayisini maksimum sayıya kadar kısıtlar. Konular kaynaga erisim talep edebilir (semaforu azaltarak) ve kaynağı kullanmayı bitirdiklerini bildirebilir(semaforu artırarak).

<a href="https://ibb.co/VYfv8Q8"><img src="https://i.ibb.co/5hb5VnV/137932019-a937f327-9e33-40b2-a0dc-6c2cc8256574.jpg" alt="137932019-a937f327-9e33-40b2-a0dc-6c2cc8256574" border="0"></a>
<a href="https://ibb.co/Hz5wjfY"><img src="https://i.ibb.co/VSfnscD/137932035-70f16c7f-9bc7-4343-aafd-102347435080.jpg" alt="137932035-70f16c7f-9bc7-4343-aafd-102347435080" border="0"></a>
<a href="https://ibb.co/09kfGQD"><img src="https://i.ibb.co/2Mwjk5n/137932058-66cfd74e-e21d-4fc5-b74c-ceae3cc95b62.jpg" alt="137932058-66cfd74e-e21d-4fc5-b74c-ceae3cc95b62" border="0"></a>
<a href="https://ibb.co/7tLbjK5"><img src="https://i.ibb.co/0yvQmrS/137932082-ddb7eed5-5671-407b-8ebb-2b8460502714.jpg" alt="137932082-ddb7eed5-5671-407b-8ebb-2b8460502714" border="0"></a>

tuvalet == paylaşılan kaynak

tuvaleti kullanan müşteriler == süreç (thread)

bekleme hattı == kuyruk

tabela sayısı == Paylaşılan kaynaklara erişebilecek süreç sayısını gösteren bazı değişkenler (semafor)

Semafor, tamsayı değeri olan bir değişkendir. Sayı, paylaşılan kaynağa erişebilecek işlem sayısı anlamına gelir. Semaforu kullanmak için aşağıdaki yapıyı oluşturun.
