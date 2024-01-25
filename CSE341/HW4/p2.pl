% Classify based on SepalWidth, PetalLength, and PetalWidth

classify(_, SepalWidth, PetalLength, PetalWidth, Class) :- % i did not use sepalLength since it have not been used in classification
    (   PetalWidth =< 0.8
    ->  Class = 'Iris-setosa'
    ;   PetalWidth > 0.8, PetalWidth =< 1.75
    ->  (   PetalLength =< 4.95
        ->  (   PetalWidth =< 1.65
            ->  Class = 'Iris-versicolor'
            ;   Class = 'Iris-virginica'
            )
        ;   PetalLength > 4.95
        ->  (   PetalWidth =< 1.55
            ->  Class = 'Iris-virginica'
            ;   (   PetalLength =< 5.45
                ->  Class = 'Iris-versicolor'
                ;   Class = 'Iris-virginica'
                )
            )
        )
    ;   PetalWidth > 1.75
    ->  (   PetalLength =< 4.85
        ->  (   SepalWidth =< 3.10
            ->  Class = 'Iris-virginica'
            ;   Class = 'Iris-versicolor'
            )
        ;   PetalLength > 4.85
        ->  Class = 'Iris-virginica'
        )
    ).
