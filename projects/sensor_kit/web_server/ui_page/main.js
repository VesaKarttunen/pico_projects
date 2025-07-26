const toggle = () => fetch('api/toggle_led');

document.getElementById('button_toggle_led').onclick = toggle;
