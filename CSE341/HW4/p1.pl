% Personels
delivery_person(john,20,8,package1,library). % Carry capacity 20kg, 8h work, currently delivering package1, currently at the library
delivery_person(alex,15,20,none,admin_office). % Carry capacity 15kg, 20h work, no current job, currently at the admin_office
delivery_person(alice,10,16,none,cafeteria). % Carry capacity 10kg, 16h work, no current job, currently at the cafeteria

% Places
place(admin_office).
place(cafeteria).
place(engineering_building).
place(lecture_hall_a).
place(institute_y).
place(library).
place(social_sciences_building).
place(institute_x).

% Edges "I have set every shortest path manually"
edge(admin_office,engineering_building,3).
edge(admin_office,lecture_hall_a,5).
edge(admin_office,institute_y,4).
edge(admin_office,library,1).
edge(admin_office,cafeteria,4).
edge(admin_office,social_sciences_building,3).
edge(admin_office,institute_x,11).

edge(engineering_building,admin_office,3).
edge(engineering_building,library,5).
edge(engineering_building,lecture_hall_a,2).
edge(engineering_building,institute_y,5).
edge(engineering_building,cafeteria,7).
edge(engineering_building,social_sciences_building,7).
edge(engineering_building,institute_x,15).

edge(lecture_hall_a,engineering_building,2).
edge(lecture_hall_a,institute_y,3).
edge(lecture_hall_a,admin_office,5).
edge(lecture_hall_a,library,6).
edge(lecture_hall_a,cafeteria,9).
edge(lecture_hall_a,social_sciences_building,8).
edge(lecture_hall_a,institute_x,16).

edge(institute_y,lecture_hall_a,3).
edge(institute_y,library,3).
edge(institute_y,engineering_building,5).
edge(institute_y,admin_office,4).
edge(institute_y,cafeteria,8).
edge(institute_y,social_sciences_building,5).
edge(institute_y,institute_x,13).

edge(library,institute_y,3).
edge(library,engineering_building,5).
edge(library,admin_office,1).
edge(library,cafeteria,5).
edge(library,social_sciences_building,2).
edge(library,lecture_hall_a,6).
edge(library,institute_x,10).

edge(cafeteria,admin_office,4).
edge(cafeteria,library,5).
edge(cafeteria,social_sciences_building,2).
edge(cafeteria,institute_x,10).
edge(cafeteria,engineering_building,7).
edge(cafeteria,lecture_hall_a,9).
edge(cafeteria,institute_y,8).

edge(social_sciences_building,cafeteria,2).
edge(social_sciences_building,library,2).
edge(social_sciences_building,institute_x,8).
edge(social_sciences_building,institute_y,5).
edge(social_sciences_building,admin_office,3).
edge(social_sciences_building,engineering_building,7).
edge(social_sciences_building,lecture_hall_a,9).

edge(institute_x,social_sciences_building,8).
edge(institute_x,cafeteria,10).
edge(institute_x,library,10).
edge(institute_x,admin_office,11).
edge(institute_x,engineering_building,15).
edge(institute_x,lecture_hall_a,16).
edge(institute_x,institute_y,13).

object(package1,5,library,engineering_building,medium,john). % I did not use prority status in objects
object(package2,3,cafeteria,lecture_hall_a,low,none).
object(package3,4,institute_x,cafeteria,high,none).

route(Source,Destination,Time):-
    edge(Source,Destination,Time),
    Source \= Destination.

route(Source,Source,0). % If source and destination are same

check_personal_availability(WorkHour,Location,From,To,TotalTime) :- % I did not take priority into account
    route(Location,From,Time1), % Time1 is the needed time for the avaialable delivery person to take the package from his/her current location
    route(From,To,Time2), % Time2 is the time needed for the available delivery person to deliver the package from the package's location
    TotalTime is Time1 + Time2,
    TotalTime =< WorkHour.

check_delivery_availability(Object) :-
    object(Object, Weight, From, To, _, _),
    (
        (delivery_person(Person, _, _, Object, _),
        write(Object), write(' is already being delivered by '), write(Person), nl);

        (not(delivery_person(_, _, _, Object, _)),
        findall((Person, TotalTime),
            (
                delivery_person(Person, Capacity, WorkHours, Job, Location),
                \+ (Job = Object),
                Weight =< Capacity,
                check_personal_availability(WorkHours, Location, From, To, TotalTime)
            ),
            Persons),
        print_available_persons(Persons))
    ).

print_available_persons(Persons) :- % Prints the available delivery persons
    (   Persons = []
    ->  write('No available delivery persons.')
    ;   foreach(
            member((Person, TotalTime), Persons),
            format('Available delivery person: ~w, Total hours to complete: ~w~n', [Person, TotalTime])
        )
    ).
