import  React, { useState } from 'react';
import ToggleButton from '@mui/material/ToggleButton';
import ToggleButtonGroup from '@mui/material/ToggleButtonGroup';
import Button from '@mui/material/Button';
import Grid from '@mui/material/Grid';
import Typography from '@mui/material/Typography';
import Slider from '@mui/material/Slider';
import Input from '@mui/material/Input';
import SendIcon from '@mui/icons-material/Send';
import Stack from '@mui/material/Stack';

export default function Home() {
    const [command, SetCommand] = useState("set_led_mode");
    const [argument, SetArgument] = useState("");

    const HandleCommandChange = (event, new_command) => {
    SetCommand(new_command);
    };
    const HandleArgumentChange = (event, new_argument) => {
    SetArgument(new_argument);
    };

    const LedModeView = () => {
        return (
            <React.Fragment>
                <Typography variant="h5" gutterBottom>Select LED mode</Typography>
                <ToggleButtonGroup
                    color="primary"
                    value={argument}
                    exclusive
                    onChange={HandleArgumentChange}
                    aria-label="Arguments"
                    >
                    <ToggleButton value="OFF">OFF</ToggleButton>
                    <ToggleButton value="ON">ON</ToggleButton>
                    <ToggleButton value="BLINKING">BLINKING</ToggleButton>
                    <ToggleButton value="BUTTON_TOGGLE">BUTTON TOGGLE</ToggleButton>
                    <ToggleButton value="BUTTON_PRESS">BUTTON PRESS</ToggleButton>
                </ToggleButtonGroup>
            </React.Fragment>
        );
    };

    const BlinkingPeriodView = () => {
        return (
            <Grid>
                <Typography id="period-slider" gutterBottom variant='subtitle1'>
                    Adjust blinking period [s]
                </Typography>
                <Grid container spacing={2} sx={{ alignItems: 'center' }}>
                    <Grid sx={{ width: 300}}>
                    <Slider
                        value={argument}
                        onChange={(e, value) => SetArgument(value)}
                        min={0}
                        max={10}
                        step={0.1}
                        aria-labelledby="period-slider"
                    />
                    </Grid>
                    <Grid>
                    <Input
                        value={argument}
                        size="large"
                        onChange={(e) => SetArgument(e.target.value)}
                        inputProps={{
                        step: 0.1,
                        min: 0,
                        max: 10,
                        type: 'number',
                        'aria-labelledby': 'period-slider',
                        }}
                    />
                    </Grid>
                </Grid>
            </Grid>
        );
    };

    const SendCommand = () => {
        fetch(`/api/${command}?arg=${argument}`);

    };

    return (
    <Stack spacing={2} sx={{ alignItems: 'center' }}>
     <Typography variant='h3'>Sensor kit UI</Typography>
     <Typography variant="h5" gutterBottom>Select command</Typography>
     <ToggleButtonGroup
      color="primary"
      value={command}
      exclusive
      onChange={HandleCommandChange}
      aria-label="Commands"
     >
      <ToggleButton value="set_led_mode">Set LED mode</ToggleButton>
      <ToggleButton value="set_led_blinking_period_s">Set LED blinking period in seconds</ToggleButton>
     </ToggleButtonGroup>
     {command === "set_led_mode" && <LedModeView />}
     {command === "set_led_blinking_period_s" && <BlinkingPeriodView />}
     {command ? <Button onClick={SendCommand} variant="contained" endIcon={<SendIcon />} sx={{ maxWidth: "15%" }}>Send command</Button> : null}

    </Stack>
    );
}