#lang scheme



(define (ask-patient-name)
  (display '(next!))
  (newline)
  (display '(who are you?))
  (newline)
  (car (read))
)

(define (main-loop)
  (let (
        (name (ask-patient-name))
        )
    (if (not (equal? name 'suppertime))
         (
          (visit-doctor name)
          (main-loop)
         )
         null
     )
  )
)

(define (visit-doctor name)
  (newline)
  (display "hello, ")(display name)(newline)
  (display '(what seems to be trouble?))
  (doctor-driver-loop name null)
)

(define (doctor-driver-loop name phrases)
  (newline)(display "**")
  (let ((user-response (read)))
    (cond ((equal? user-response '(goodbye))
              (display "goodbye, ")(display name)(newline)(print '(see you next week))(newline))
          (else (display (reply user-response phrases))
                (doctor-driver-loop name (cons user-response phrases)))
    )
  )
)

; Стратегии - список списоков, по убыванию приоритета. 
; среди одинаковых приоритетов выбирается рандомно 
; (
;  ((pred1 lambda1) (pred2 lambda2)) ; самый большой приоритет

;  ((pred3 lambda3) (pred4 lambda4) (pred5 lambda5)) ; приоритет поменьше
; )

(define (reply user-response phrases)
  (let (
        (strategies
         
         (list 
          
          (list
           (list (lambda () (< (length user-response) 3)) (lambda () '(Could you say more?)))
          ); -- наибольший приоритет имеет проверка длины фразы
          
          (list
           (let
               ((l (keyword-patterns user-response)))
             (list (lambda () (not (null? l))) (lambda () (pick-random l))))
          ); -- чуть меньше - проверка ключевых слов
          
          (list
           (list
            (lambda () #t)
            (lambda () (append (qualifier) (change-person user-response))))
           (list
            (lambda () #t)
            hedge)
           (list (lambda () (not (null? phrases))) (lambda () (append '(earlier you said that) (change-person (pick-random phrases)) )))
           (list (lambda () (not (null? someTree))) (lambda () (treeGeneratePhrase someTree)))
          ); -- минимальный приоритет имеют общие фразы
        )        
       )
      )
    
    ((pick-random
      (car
       (filter
        (lambda (l) (not (null? l)))
        (map 
         (lambda (l) (map
                      cadr
                      (filter
                       (lambda (x) ((car x)))
                       l)))
         strategies)))))
  )
)

(define (fifty-fifty) (= (random 2) 0))

(define (qualifier)
  (pick-random '( (you seem to think)
                  (you feel that)
                  (why do you believe)
                  (why do you say)
                  (are you sure)
                )
  )
)

(define (hedge)
  (pick-random '( (please go on)
                   (please continue)
                   (many people have the same sorts of feelings)
                   (many of my patients have told me the same thing)
                   (I agree with you)
                 )
   )
)

(define (find p l)
(if (equal? l null)
      null
      (if (p (car l))
          (car l)
          (find p (cdr l))
      )
  )
)

(define (replace replacement-pairs word)
  (let (
        (pair (find (lambda (x) (equal? (car x) word)) replacement-pairs))
       )
    (if (null? pair)
        word
        (cadr pair)
    )
  )
)

(define (many-replace replacement-pairs lst)
  (map (lambda (word) (replace replacement-pairs word)) lst)
)

(define (change-person phrase)
  (many-replace '((i you)
                  (me you)
                  (am are)
                  (my your)
                  (are am)
                  (you i)
                  (your my)
                 )
                phrase
  )
)

(define (decart l1 l2) ; декартово произведение двух списков
  (reduced append (map (lambda (x) (map (lambda (y) (list x y)) l2)) l1) null )
)

(define (apply-keyword-pattern pattern phrase)
  (let (
        (keys (filter (lambda (key) (not (null? (find (lambda (x) (equal? key x)) phrase)))) (car pattern)))
        (patterns (cadr pattern))
       )
    (map (lambda (pair) (many-replace (list (list '* (car pair))) (cadr pair) )) (decart keys patterns))
  )
)

(define (apply-keyword-patterns patterns phrase)
  (reduced append (map (lambda (pattern) (apply-keyword-pattern pattern phrase) ) patterns ) null)
)

(define (keyword-patterns phrase)
  (apply-keyword-patterns
   '( ((depressed suicide)
      ((when you feel depressed, go out for ice cream)
       (depression is a disease that can be treated)))
     ((mother father parents)
      ((tell me more about your *)
       (why do you feel that way about your * ?)))
     ) phrase)
)

(define (pick-random lst)
  (nth (random (length lst)) lst)
)

(define (nth number lst)
   (if (= number 0) (car lst)
       (nth (- number 1) (cdr lst))
    )
)

(define (filter f l)
  (if (equal? l null)
      null
      (if (f (car l))
          (cons (car l) (filter f (cdr l)))
          (filter f (cdr l))
      )
  )
)

(define (reduce f l)
  (if (equal? (length l) 1)
      (car l)
      (f (car l) (reduce f (cdr l)))
  )
)

(define (reduced f l d)
  (if (null? l)
      d
      (f (reduced f (cdr l) d) (car l))
  )
)

(define (sum lst) (reduced + lst 0))

(define (repeat n x) (if (equal? n 0) '() (cons x (repeat (- n 1) x))))

(define (list->symbol lst) (string->symbol (list->string lst)))

(define (symbol->list sym) (string->list (symbol->string sym)))

(define (has lst n) (if (equal? n 0) #t (if (null? lst) #f (has (cdr lst) (- n 1)))))

(define (exists? key lst) (if (null? lst) #f (if (equal? key (car lst)) #t (exists? key (cdr lst)))))

(define (take lst n) (if (equal? n 0) null (cons (car lst) (take (cdr lst) (- n 1) ))))

; дерево - это  список списков следующего вида:
; ('x', N, branch)
; первый элемент - char или 'treeEndOfList
; второй - количество фраз, которые попадали в эту ветвь
; третий - само поддерево

; public
(define treeEmpty null)

; (applyToOrDefault '(1 2 4 5 10 8) (lambda (x) (> x 90)) (lambda (x) (* x x)) (- 1))
;  (1 2 4 5 10 8 1)
; (applyToOrDefault '(1 2 4 5 10 8) (lambda (x) (> x 9)) (lambda (x) (* x x)) (- 1))
;  (1 2 4 5 100 8)

; private
(define (applyToOrDefault lst pred f def)
  (if (null? lst)
      (list (f def))
      (if (pred (car lst))
          (cons (f (car lst)) (cdr lst))
          (cons (car lst) (applyToOrDefault (cdr lst) pred f def))
      )
  )
)

; private
(define (treeMemoizeList_ tree phrase)
  (if (null? phrase)
      tree
      (let ((first  (car phrase))
            (others (cdr phrase))
           )
        (applyToOrDefault
         tree
         (lambda (branch) (equal? (car branch) first))
         (lambda (branch) (list (car branch) (+ (cadr branch) 1) (treeMemoizeList_ (caddr branch) others)))
         (list first 0 null)
        )
      )
  )
)

; private
(define (treeMemoizeList tree characterList)
  (treeMemoizeList_ tree (append characterList '(treeEndOfList)))
)

; private
(define (skip-weighted n weigher lst)
  (let ((weight (weigher (car lst))))
    (if (<= weight n)
        (skip-weighted (- n weight) weigher (cdr lst))
        lst
    )
  )
)

; private
(define (pick-random-weighted weigher lst)
  (let ((total (sum (map weigher lst))))
    (car (skip-weighted (random total) weigher lst))
  )
)

; private
(define (treeChooseWeightedRandomList tree)
  (let ((choosenOne (pick-random-weighted cadr tree)))
   (if (equal? (car choosenOne) 'treeEndOfList)
       '()
       (cons (car choosenOne) (treeChooseWeightedRandomList (caddr choosenOne)))
   )
  )
)

; private
(define (getSubTreeByPrefixCharacter tree char)
  (caddr
   (find
    (lambda (branch) (equal? (car branch) char))
    tree
   )
  )
)

; private
(define (getSubTreeByPrefixList tree prefix)
  (reduced getSubTreeByPrefixCharacter (reverse prefix) tree)
)

; private
(define (makeCharacterListFromSymbols lst)
 (reduce
  append
  (map
   (lambda (sym) (append 
                         (symbol->list sym)
                         (list 'wordSeparator)
                 )
   )
   lst
  )
 )
)

; public; editable
(define contextLength 2)

; public
; при последовательных вызовах этой функции надо передавать списки одинаковой длины (contextLength + 1)
; возвращает новое дерево, полученное при добавлении данного списка в старое
(define (treeMemoizeListOfSymbols tree lst)
  (let ((characterList (makeCharacterListFromSymbols lst)))
    (treeMemoizeList tree characterList)
  )
)

; public
; переданный контекст должен быть префиксом длины contextLength каких-либо списков переданных ранее в treeMemoizeListOfSymbols
; возвращает последний символ, распределение возвращаемых значений соотвестствует распределению входны данных
(define (treeChooseSymbolByContext tree context)
  (let ((contextCharacterList (makeCharacterListFromSymbols context)))
    (let ((contextTree (getSubTreeByPrefixList tree contextCharacterList)))
      (let ((choosenList (treeChooseWeightedRandomList contextTree)))
        (list->symbol (reverse (cdr (reverse choosenList))))
      )
    )
  )
)

; private
(define (treeMemoizePhrase_ tree phrase)
  (if (has phrase (+ contextLength 1))
      (let ((data (take phrase (+ contextLength 1))))
        (treeMemoizePhrase_ (treeMemoizeListOfSymbols tree data) (cdr phrase))
      )
      tree
  )
)

; public
; запомнить все контексты заданной последовательности символов
; возвращается новое дерево
(define (treeMemoizePhrase tree phrase)
  (treeMemoizePhrase_ tree (append (repeat contextLength 'beforePhrase) (append phrase '(afterPhrase))))
)

; private
(define (treeGeneratePhrase_ tree context)
  (let ((word (treeChooseSymbolByContext tree context)))
    (if (equal? word 'afterPhrase)
        null
        (cons word (treeGeneratePhrase_ tree (append (cdr context) (list word))))
    )
  )
)

; public
; генерировать случайную фразу, используя статистику в дереве
; дерево не модифицируется
(define (treeGeneratePhrase tree)
  (treeGeneratePhrase_ tree (repeat contextLength 'beforePhrase))
)

; public
(define endsOfPhrase (string->list ".!?…"))
(define spaceSymbols (list #\space #\newline #\tab #\return #\linefeed))

; private
(define (parseChar chars)
  (list (car chars) (cdr chars))
)

; private
(define (parseWord chars)
  (let ((letter_rest (parseChar chars)))
    (let ((letter (car letter_rest))
          (rest (cadr letter_rest))
          (isPhraseEnd (exists? (car letter_rest) endsOfPhrase))
         )
      (if (exists? letter spaceSymbols)
          (list null rest #f)
          (if (null? rest)
              (list (list letter) rest #t)
              (let ((word_rest (parseWord rest)))
                (let ((nextWord (car word_rest))
                      (nextRest (cadr word_rest))
                      (nextIsPhraseEnd (caddr word_rest))
                      )
                  (list (cons letter nextWord)
                        nextRest
                        (if (null? nextWord)
                            isPhraseEnd
                            nextIsPhraseEnd
                        )
                  )
                )
              )
          )
       )
    )
  )
)

; private
(define (parsePhrase chars)
  (let ((word_rest (parseWord chars)))
    (let ((word (car word_rest))
          (rest (cadr word_rest))
          (isPhraseEnd (caddr word_rest)))
      (if (or isPhraseEnd (null? rest))
          (list (if (null? word) null (list (list->symbol word))) rest)
          (let ((phrase_rest (parsePhrase rest)))
            (let ((phrase (car phrase_rest))
                  (prest (cadr phrase_rest)))
              (if (null? word)
                  (list phrase prest)
                  (list (cons (list->symbol word) phrase) prest)
              )
            )
          )
      )         
    )
  )
)

; private
(define (parseText_ chars)
  (if (null? chars)
      null
      (let ((phrase_rest (parsePhrase chars)))
        (let ((phrase (car phrase_rest))
              (rest (cadr phrase_rest)))
          (if (null? phrase)
              (parseText_ rest)
              (cons phrase (parseText_ rest))
          )
        )
      )
  )
)

; public
; преобразует строку с текстом в список фраз, составленных из символов
(define (parseText text)
  (parseText_ (string->list text))
)

; public
(define (treeMemoizeText tree text)
  (reduced treeMemoizePhrase (parseText text) tree)
)

;;;; TEST AREA

;(define someTree (reduced treeMemoizeString (list "abc" "abd") treeEmpty))

;(map (lambda (n) (treeChooseWeightedRandomString someTree)) (repeat 16 1))

;(define someSubTree (getSubTreeByPrefixCharacter someTree #\a))
;(define someSubTree (getSubTreeByPrefixList someTree (string->list "ab")))

;(map (lambda (n) (treeChooseWeightedRandomString someSubTree)) (repeat 16 1))
;(makeCharacterListFromSymbols '(ab abc abd))
;(define someTree (reduced treeMemoizeListOfSymbols  '(
;                                                      (Hello world)
;                                                      (Good bye)
;                                                      (Good work)
;                                                      (Good game)
;                                                      ) treeEmpty))
;(map (lambda (n) (treeChooseSymbolByContext someTree '(Good ))) (repeat 16 1))
         
;(define someTree (reduced treeMemoizePhrase '(
;                                              (Hello world!)
;                                              (I am the best of the best)
;                                              (Where are you?)
;                                              (Here am i)
;                                              (I glad to see you)
;                                              (Are you crazy?)
;                                              (How do you do?)
;                                              (Are you ready for the lesson?)
;                                              (Do you speak English?)
;                                              (Yes I do)
;                                              (What is it?)
;                                             ) treeEmpty))
;someTree
;(map (lambda (n) (treeGeneratePhrase someTree)) (repeat 160 1))


(define someTree (treeMemoizeText treeEmpty
"

Девушка шла мне навстречу. Я даже не успел всмотреться в ее глаза, голубые, как лишенное озона небо Антарктиды, не успел разглядеть улыбки, способной укротить голодного тигра. Я понял — это Она. Та, кого я искал всю жизнь, все двадцать два года.


А девушка проходила мимо. Она шла, погруженная в свои мысли, и даже не смотрела в мою сторону. Еще мгновение — и мы навсегда разойдемся в огромном городе. И я начал действовать.


Был очень жаркий день, улица кипела прохожими. Это осложняло ситуацию, но я все же решился. Закрыл глаза, произнес формулу перехода. И мгновенно оказался в пятом измерении. Здесь было тихо, сыро и уютно. Пятимерные существа скользили сразу в двух направлениях, не обращая на меня никакого внимания. Я для них был чем-то вроде мелового рисунка на асфальте. Оглядевшись, я приступил к выполнению своего плана. Порвал парочку силовых линий, исказил несколько полей. И вернулся в наш мир.


Жара осталась, и улица, заполненная прохожими, никуда не делась. Но девушка, с которой мы уже разминулись, снова шла мне навстречу — мои манипуляции в пятом измерении искривили пространство. Увы. И на этот раз Она не посмотрела на меня.


Я опять вернулся в пятое измерение. Снова искривил пространство. И еще раз. И еще. Девушка, не замечая этого, теперь ходила вокруг меня по кругу. Но по-прежнему не смотрела в мою сторону.


Тогда я искривил пространство так, что мы неминуемо должны были столкнуться. Вернулся на улицу — и почувствовал холодок в груди. Высотный дом невдалеке не выдерживал искривлений пространства и теперь разваливался. Два или три верхних этажа уже летели вниз. Но прежде чем обломки стен коснулись асфальта, я произнес заклятье временного перехода. И оказался в прошлом, в самом разгаре застойного времени. Улица была почти та же, но высотный дом только строился. На ходу обретая невидимость, я направился к стройке. Понадобилось несколько минут, чтобы во всем разобраться: прораб Михайлов машинами воровал бетон.


Неудивительно, что через десять лет дом не выдержал заурядного искривления пространства...


Я отправился в соседнее СМУ. Там мне пришлось перевоплотиться в бригадира монтажников Петра Зубило и выступить с почином: «Высотным домам — высокую гарантию». Почин поддержали в высоких кругах. ОБХСС проверил работу прораба Михайлова.


Прораб получил десять лет с конфискацией, а дом был построен из качественного цемента. Убедившись в этом, я вернулся обратно.


Теперь дом не рассыпался, а девушка шла мне навстречу.


Столкновение было неизбежным, и мы действительно столкнулись.


— Извините, — не поднимая глаз, сказала девушка. И прошла дальше…


Не думайте, что я пал духом. Как бы не так. Волевым усилием я сгреб над Атлантическим океаном несколько дождевых туч и развесил их над городом. Полил дождь, смывая жару, бензиновую вонь.


Материализовав из воздуха красивый японский зонтик, я подошел к девушке.


— Вы вымокнете, разрешите, я вас провожу.


— Я люблю ходить под дождем.


На этот раз она взглянула на меня, но без всякого интереса.


И меня осенило: а вдруг ей просто не нравятся такие, как я маленькие, толстые, рыжеволосые мужчины?


В школе магов (я забыл объяснить, что когда-то учился там) имелся специальный курс — глубокое проникновение в прошлое. Сейчас я решил испробовать это рискованное, но сильнодействующее средство. И новое заклятие отправило меня в конец девятнадцатого века.


В то время прапрадед, встреченной мною незнакомки, служил корнетом в кавалерийском полку. Я поступил в тот же полк, сдружился с корнетом и однажды, глубокой ночью, передвинул в его седьмой хромосоме адениновое основание со сто тридцать шестого витка спирали ДНК на двести четырнадцатый. Результатом этого должна была стать любовь праправнучки корнета к невысоким, полным и рыжеволосым мужчинам.


Сознаю, что это был очень даже неэтичный поступок, но иначе я не мог…


Вернувшись, я попал под проливной дождь. Искривление пространства тоже продолжалось, и девушка ходила вокруг меня. Но не одна.


Привставая на цыпочки, над ней нес зонт юноша — еще более невысокий, полный и рыжий, чем я сам.


Рядом с ним у меня не было никаких шансов.


Задрожавшим голосом я произнес формулу Исходной Ситуации. И все вернулось на круги своя. Пространство выпрямилось, тучи с гулом унеслись к Атлантике, девушка в полном одиночестве шла мне навстречу, высотный дом держался не на бетоне, а на честном слове прораба Михайлова.


У меня оставался последний шанс. И я рискнул. Когда мы с незнакомкой поравнялись, я небрежно произнес:


— Здравствуй!


Она удивленно подняла брови. Спросила:


— Разве мы знакомы?


— Нет, — бледнея ответил я. — Но, может быть, мы познакомимся?


Девушка рассмеялась. И сказала:


— Давайте. А то вы уже полчаса ходите вокруг меня кругами!
"
))

;(display (map (lambda (n) (treeGeneratePhrase someTree)) (repeat 16 1)))

;;;; END OF TEST AREA


(main-loop)
