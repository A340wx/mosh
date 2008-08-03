(let* ([color->rgb (lambda (c) (cons 'rgb c))]
       [:point (make-record-type-descriptor 'point #f #f #f #f
                                            '#((mutable x) (mutable y)))]
       [:point-cd (make-record-constructor-descriptor :point #f #f)]
       [:point-cd/abs (make-record-constructor-descriptor
                       :point #f
                       (lambda (new)
                         (lambda (x y)
                           (new (abs x) (abs y)))))]
       [:cpoint (make-record-type-descriptor
                 'cpoint :point
                 #f #f #f
                 '#((mutable rgb)))]
       [cpoint-rgb
        (record-accessor :cpoint 0)]
       [make-cpoint(record-constructor
                    (make-record-constructor-descriptor
                     :cpoint :point-cd
                     (lambda (p)
                       (lambda (x y c)
                         ((p x y) (color->rgb c))))))])
  (cpoint-rgb (make-cpoint -1 -3 'red)))
