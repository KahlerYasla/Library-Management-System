void kitapListele(Kitap *kitapListesi)
{
    printf("\nKitap Listesi:\n");
    Kitap *iter = kitapListesi;

    while (iter != NULL)
    {
        printf("Ad: %s, ISBN: %s, Adet: %d\n", iter->kitapAdi, iter->ISBN, iter->adet);

        kitapOrnekListele(iter->head);

        iter = iter->next;
    }
}