-- Mostrar o filme com duração de 4 dias ou
-- mais de locação e o funcionário que realizou

use sakila;

drop view vw_funcionario;

create view vw_funcionario as
select f.title as filme, func.first_name as funcionario
from film f inner join inventory I on f.film_id = I.film_id
inner join rental A on I.inventory_id = A.inventory_id
inner join staff func on A.staff_id = func.staff_id
where f.rental_duration >= 4 group by f.title, func.first_name;

select filme, funcionario from vw_funcionario;


