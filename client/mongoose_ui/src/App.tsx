import { useEffect, useState } from 'preact/hooks';

export function App() {
  const [message, setMessage] = useState('Ladataan...');

  useEffect(() => {
    fetch('/api/hello')
      .then(res => res.text())
      .then(text => setMessage(text))
      .catch(err => setMessage('Virhe: ' + err.message));
  }, []);

  return (
    <main class="p-4">
      <h1 class="text-xl font-bold">Palvelimen vastaus:</h1>
      <p>{message}</p>
    </main>
  );
}
