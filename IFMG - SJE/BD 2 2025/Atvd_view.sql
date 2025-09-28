use sakila;

create view vw_funcionario as
select f.title as filme, func.first_name as funcionario
from film f inner join inventory I on f.film_id = I.film_id
inner join rental A on I.inventory_id = A.inventory_id
inner join staff func on A.staff_id = func.staff_id
where f.rental_duration >= 4 group by f.title, func.first_name;

/*1. Crie uma view chamada filme_em_estoque que liste os filmes disponíveis em estoque
para cada loja. A view deve incluir o nome do filme, o ID da loja e o status de disponibilidade.*/
 
create or replace view vw_filme_em_estoque as
select f.title as nome_do_filme, s.store_id as id_da_loja, i.inventory_id,
if(i.inventory_id in (select inventory_id from rental where return_date is null), 'Alugado', 'Disponível') as status
from inventory i join film f on i.film_id = f.film_id join store s on i.store_id = s.store_id;

select * from vw_filme_em_estoque;

/*2. Crie uma view chamada clientes_vips que mostre os clientes que fizeram mais de 30
locações. A view deve exibir o nome do cliente, o número de locações e a cidade de
residência.*/

create or replace view vw_clientes_vips as
select c.first_name as nome_cliente, ci.city as cidade_residencia, count(r.rental_id) as qtd_locacoes
from customer c join rental r on r.customer_id = c.customer_id
join address ad on ad.address_id = c.address_id 
join city ci on ci.city_id = ad.city_id
group by c.first_name, ci.city
having count(r.rental_id) > 30;

select * from clientes_vips;

/*3. Crie uma view chamada receita_por_categoria que calcule a receita total por categoria 
de filme. A view deve incluir o nome da categoria e a receita total gerada.*/

create or replace view vw_receita_por_categoria as
select ca.name as name_categoria, sum(pa.amount) as receita_total 
from film_category fc join film f on f.film_id = fc.film_id
join inventory inv on inv.film_id = f.film_id
join category ca on ca.category_id = fc.category_id
join rental re on re.inventory_id = inv.inventory_id
join payment pa on pa.rental_id = re.rental_id
group by ca.name;

select * from receita_por_categoria;

/*4. Crie uma view que liste os clientes que não locaram filmes nos últimos 6 meses. A view
deve incluir o nome do cliente, o ID do cliente, a data da última locação e a cidade.*/

create or replace view vw_clientes_inativos_ultimo_semestre as
select c.customer_id as cliente_id, c.first_name as nome_cliente, ci.city as cidade, max(re.rental_date) as data_ultima_locacao
from customer c join rental re on re.customer_id = c.customer_id
join address ad on ad.address_id = c.address_id
join city ci on ci.city_id = ad.city_id
group by c.customer_id, c.first_name, ci.city
having max(re.rental_date) < date_sub(curdate(), interval 6 month) order by c.customer_id;

select * from vw_clientes_inativos_ultimo_semestre;

/*5. Crie uma view que mostre a receita total gerada por filmes de cada categoria nos últimos
12 meses. A view deve incluir o nome da categoria, a receita total, e a quantidade de filmes locados.*/

create or replace view vw_receita_categoria_ultimo_ano as
select ca.name as nome_categoria, sum(pa.amount) as receita_total, count(re.rental_id) as qtd_filmes_locados
from category ca join film_category fc on fc.category_id = ca.category_id
join film fi on fi.film_id = fc.film_id
join inventory inv on inv.film_id = fi.film_id
join rental re on re.inventory_id = inv.inventory_id
join payment pa on pa.rental_id = re.rental_id
where re.rental_date >= date_sub(curdate(), interval 12 month)
group by ca.name;

select * from vw_receita_categoria_ultimo_ano;

/* 6. Crie uma view que liste os filmes que têm a maior taxa de locação em cada categoria. A
view deve incluir o nome do filme, a categoria, a quantidade de locações e a receita total
gerada por esse filme.*/
 

create or replace view vw_maior_locacao_categoria as
with RankedFilms as
(select fi.title as nome_filme, ca.name as nome_categoria, count(re.rental_id) as qtd_locacoes, sum(pa.amount) as receita_total,
rank() over (partition by ca.name order by count(re.rental_id) desc) as rank_locacao
from film fi join film_category fc on fc.film_id = fi.film_id
join category ca on ca.category_id = fc.category_id
join inventory inv on inv.film_id = fi.film_id
join rental re on re.inventory_id = inv.inventory_id
join payment pa on pa.rental_id = re.rental_id
group by fi.title, ca.name)
select nome_filme, nome_categoria, qtd_locacoes, receita_total
from RankedFilms where rank_locacao = 1;

select * from vw_maior_locacao_categoria;

/*7. Crie uma view que fornece uma análise da rentabilidade dos diferentes gêneros de filmes
disponíveis e exiba o gênero do filme, a receita total gerada por filmes daquele gênero, o
número de filmes no gênero e a receita média por filme.*/

create or replace view vw_rentabilidade_genero as
select ca.name as genero, sum(pa.amount) as receita_total, count( distinct fi.film_id) as qtd_filmes, round(sum(pa.amount) / count(distinct fi.film_id), 2) as receita_media
from film fi join film_category fc on fc.film_id = fi.film_id
join category ca on ca.category_id = fc.category_id
join inventory inv on inv.film_id = fi.film_id
join rental re on re.inventory_id = inv.inventory_id
join payment pa on pa.rental_id = re.rental_id
group by ca.name;

select * from vw_rentabilidade_genero;

