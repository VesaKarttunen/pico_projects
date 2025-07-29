function SendCommand() {
    const command  = document.getElementById('command').value;
    const argument = document.getElementById('argument').value;

    fetch(`/api/${command}?arg=${argument}`);
}

document.getElementById('button_send_command').onclick = SendCommand;
