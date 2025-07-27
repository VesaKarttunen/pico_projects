import { useEffect, useState } from 'preact/hooks';

export default function Home() {

const [message, setMessage] = useState('Ladataan...');

  useEffect(() => {
    fetch('http://192.168.101.173/api/hello')
      .then(res => res.text())
      .then(text => setMessage(text))
      .catch(err => setMessage('Virhe: ' + err.message));
  }, []);




    return(
        <div>
            <h1>Palvelimen vastaus:</h1>
            <p>{message}</p>
        </div>
    );
}