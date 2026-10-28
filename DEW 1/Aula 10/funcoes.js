function adicionarTarefa(){
    const lista = document.getElementById('lista');
    const novaTarefa = document.getElementById('input-tarefa');

    if (novaTarefa.value.trim() === '') {
        alert('Por favor, digite uma tarefa!');
        return; 
    }
  
    const novoItem = document.createElement('li');
    novoItem.textContent = novaTarefa.value;
    lista.appendChild(novoItem);
    novaTarefa.value = '';
    novaTarefa.focus();
}