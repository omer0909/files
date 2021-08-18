/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuchill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 21:00:24 by apuchill          #+#    #+#             */
/*   Updated: 2019/11/25 21:00:27 by apuchill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_putchar(char a) // yadırır
{
	write(1, &a, 1);
}

void ft_putvet(int vet[], int n) // tüm basamkaları teker teker yazdırır
{
	int c; 

	c = 0;		  
	while (c < n) 
	{
		ft_putchar(vet[c] + '0'); // bu toplama işlemi int veri türü char türüne dönüştüğü için yapılır. çünkü ascii karakter tablosunda 0 ın sırası 48. sıradır. 
		c++;
	}
}

int ft_get_index(int combn[], int n)
{
	int c;	 // basamaklar arası sayaç
	int max; // basamağın maksimum değerini yazar (10 olduğuna bakmayın while içinde küçüktür olduğu için 10, normalde 9)

	c = 0; 
	max = 10 - n; 
	while (c < n) // basamakları gezer. en yüksek basamaktan başlar. en yüksek basamak 0. index'e eşittir
	{
		if (combn[c] == max)// en son basamak 0 olduğu için o max değerine ulaşınca, -1 gönderip döngüyü durdurur. 
		                    // ama eğer en son basamak değilse kendinden yüksek bir sonraki basamağa arttırma emri verir. (dolaylı)
			return (c - 1);

		if (c == (n - 1) && combn[c] < max)// yukarıdaki döngü kendinden büyük basamakları arttırdığı için birler basamağını arttıracak basamak olmaz.
		                                   // bu yüzden birler basamağını burası arttırır.
			return (c);
		c++;
		max++;
	}
	return (-1);
}

void ft_increment(int vet[], int n, int index)
{
	int c;

	c = index + 1; // girilen basamaktan 1 aşağıdaki basamak seçilerek döngü buradan başlatılır
	vet[index]++;  // girilen basamktaki değer arttırılır
	while (c <= n) // döngüde istenilen basamaktan aşağıda olan bütün basamaklar dolaşılır
	{
		vet[c] = vet[c - 1] + 1; // basamaktaki rakam kendinden 1 basamak yukarıda olan rakamın, 1 fazlası olacak şekilde ayarlanır.
		c++;
	}
}

// ön bilgi! burada bir sayının kombinasyonlarını yazarken birler basamağı her zaman onlar basamağından büyük olmak zorunda. 
// bu durum tüm büyük basamaklar için geçerli örneğin 4 basamaklı bir sayı için basamaklarındaki rakamlar 4. < 3. < 2. < 1. olmak zorunda
// bu yüzden mesela 2. basamktaki rakamın en çok 8 olabilmesine neden oluyor. çünkü birler basamağı max 9 olabilir.

void ft_print_combn(int n) // bu kodda bsamak sayısı girilen kodun tüm rakamsal kombinasyonları yazdırılır.
{
	int combn[n];  // burada basamak sayısı girilen sayıın tüm basamkalarını array indexlerine ayırmak için bir array oluşturulur
	int c;		   // while loop için sayaç değişken
	int pos_index; // sayının hangi basamağında olduğumuzu tutan değişken

	if (n >= 10 || n <= 0) // basamak sayısı grilen değer bu aralıklarda olmazsa hata verir
		return;
	else 
	{
		c = 0;		  
		while (c < n) // yazmaya başlayacağımız ilk sayıyı arraydaki basamklara yazdırır. bu sayı örneğin 4 basamaklı olduğu zaman 0123 şeklindedir
		{
			combn[c] = c;
			c++;
		}
		while (ft_get_index(combn, n) != -1)    // kontrol ettiği şey en yüksek basamağın max değerine ulaşıp ulaşmadığı
		{
			pos_index = ft_get_index(combn, n); // arttırılacak indexi belirleme
			ft_putvet(combn, n);                // yazdırma
			ft_increment(combn, n, pos_index);  // arttırma
			write(1, ", ", 2);					// sayıların arasına virgül koyar
		}
		ft_putvet(combn, n); // en son arttırmayı yapar ama while döngüsü son değer olduğu için döngüye sokmaz. bu yüzden en son değeri yazdırır.
	}
}
int main()
{
	ft_print_combn(4);
}
