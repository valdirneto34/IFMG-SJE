function adicionarTarefa(){
    const lista = document.getElementById('lista');
    const novaTarefa = document.getElementById('input-tarefa').textContent;
    const novoItem = document.createElement('li');
    novoItem.textContent = novaTarefa;
    lista.appendChild(novoItem);
}